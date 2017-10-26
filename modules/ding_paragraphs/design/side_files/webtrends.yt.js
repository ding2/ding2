/*
Copyright (c) 2015 Webtrends, Inc.
YouTube Plugin v10.4.22
  
An example of including the plugin with your tag.
  
<script type="text/javascript">
// async loader function, called by webtrends.js after load
window.webtrendsAsyncInit=function(){
var dcs=new Webtrends.dcs().init({
dcsid:"YOUR_WEBTRENDS_DCSID_HERE",
timezone:YOUR_TIMEZONE_HERE,
plugins:{
yt:{src:"//s.webtrends.com/js/webtrends.yt.js",	mode:"manual", dcsid:"YOUR_WEBTRENDS_YOUTUBE_DCSID"}
}
}).track();
};
(function(){
var s=document.createElement("script"); s.async=true; s.src="//s.webtrends.com/js/webtrends.js";
var s2=document.getElementsByTagName("script")[0]; s2.parentNode.insertBefore(s,s2);
}());
</script>
*/
(function (_window, _document) {

	if (!_window.Webtrends || _window.WTYT)
		return;

	WTYT = function (t, p) {
		this.tag = t;
		this.pluginConfig = p;

		//modes
		//automatic = plugin will create players for iFrame embedded players
		//manual = plugin will not create players for iFrame embedded players. The user is required to
		//pass in a reference to any players that should be tracked.
		this.mode = (this.pluginConfig.mode) ? this.pluginConfig.mode : "automatic";

		//The user may want to provide a different dcsid for the youtube data
		this.maindcsid = this.tag.dcsid;
		this.dcsid = (this.pluginConfig.dcsid) ? this.pluginConfig.dcsid : this.tag.dcsid;

		//Used to keep track of all active players on the page
		this.activePlayers = [];
		this.activePlayerCount = 0;

		//Used to keep track of players which have been identified
		//but aren't ready to have their listeners added yet
		this.unreadyPlayers = [];

		//Video progress is broken up into these chunks to track.
		//For example, a value of 10 will cause the progess to be
		//tracked at 10%, 20%, 30%, etc.
		this.percentageIncrements = 25;

		//Seeking/Skipping around in videos results in 
		//multiple events being fired but we only want to react to the last one. 
		//We need to throttle events and hold them back to ensure that another 
		//one won't come in immediately after it.
		this.throttleInterval = 500; //in milliseconds		
		this.throttledEvents = [];
		this.throttleTimeouts = [];

		//Debugging
		this.errors = [];
	}

	WTYT.prototype = {

		wrapYTCallback: function () {

			var self = this;
			//user has defined their own callback
			if (window.onYouTubeIframeAPIReady) {
				var origOnYouTubePlayerAPIReady = window.onYouTubeIframeAPIReady;
				window.onYouTubeIframeAPIReady = function () {
					origOnYouTubePlayerAPIReady();
					self.startPlugin();
				};
			}
			//user has not defined their own callback
			else {
				window.onYouTubeIframeAPIReady = function () {
					self.startPlugin();
				};
			}
		},
		wrapYTPlayerReadyCallback: function () {
			//User has defined their own player ready callback
			var self = this;
			if (window.onYouTubePlayerReady) {
				var origOnYouTubePlayerReady = window.onYouTubePlayerReady;
				window.onYouTubePlayerReady = function () {
					self.purgeUnreadyPlayers();
					self.init_embed(); //To catch any players that weren't yet visible on the first pass
					origOnYouTubePlayerReady();
				}
			}
			//User has not defined their own callback
			else {
				window.onYouTubePlayerReady = function () {
					self.purgeUnreadyPlayers();
				}
			}
		},
		startPlugin: function () {
			if (this.mode === "automatic") {
				this.init_iFrame();
			}
			this.init_embed();
			this.startProgressCheck();
		},
		init_iFrame: function () {

			//Look for iFrame embedded players
			var iframes = document.getElementsByTagName("IFRAME");
			for (var i = 0; i < iframes.length; i++) {

				if (iframes[i].src && iframes[i].src.toLowerCase().indexOf("://www.youtube.com/embed/") >= 0) {

					var self = this;
					var player = new YT.Player(iframes[i], {
						id: i,
						playerVars: { enablejsapi: 1 },
						events: {
							'onReady': function (event) {
								self.addActivePlayer(event.target);
							},
							'onStateChange': Webtrends.ytTracker.iFrameStateChanged,
							'onPlaybackQualityChange': Webtrends.ytTracker.iFrameQualityChanged
						}
					});
				}
			}
		},
		init_embed: function () {

			/*********************************
			The players identified below may not be "ready" so we have to first check. If they are ready
			we go ahead and add the listener. If they are not ready we have to wait for the onYoutubePlayerReady
			callback to be called. As with the API ready callback we have to make sure that we don't interfere
			with a user defined player ready callback. See the wrapYTPlayerReadyCallback below.
			*********************************/
			//Look for players embedded using SWFObject
			var objs = document.getElementsByTagName("OBJECT");
			if (objs) {
				for (var i = 0; i < objs.length; i++) {

					var dataAtt = objs[i].getAttribute("data");
					if ((dataAtt && dataAtt.toLowerCase().indexOf("://www.youtube.com/") >= 0) || //FF and Chrome
						 (objs[i].Movie && objs[i].Movie.toLowerCase().indexOf("://www.youtube.com/"))  //IE 
						 ) {
						objectPlayer = objs[i];

						//Player already identified
						if (objectPlayer.hasOwnProperty("wtid"))
							continue;

						//Player is ready, continue
						if (objectPlayer.getPlayerState) {
							this.addEmbedPlayer(objectPlayer);
						}
						//Player is not ready, queue it up
						else {
							this.unreadyPlayers[this.unreadyPlayers.length] = objectPlayer;
						}
					}
				}
			}

			//Look for videos in EMBED
			var embeds = document.getElementsByTagName("EMBED");
			if (embeds) {
				for (var i = 0; i < embeds.length; i++) {
					var srcAtt = embeds[i].getAttribute("src");
					if (srcAtt && srcAtt.toLowerCase().indexOf("://www.youtube.com/") >= 0) {
						embedPlayer = embeds[i];

						//Player already identified
						if (embedPlayer.hasOwnProperty("wtid"))
							continue;

						//Player is ready, continue
						if (embedPlayer.getPlayerState) {
							this.addEmbedPlayer(embedPlayer);
						}
						else {
							this.unreadyPlayers[this.unreadyPlayers.length] = embedPlayer;
						}
					}
				}
			}
		},
		purgeUnreadyPlayers: function () {
			/* 
			This function will iterate over all inactive players and identify any that are now active.
			It will attach the event listener to those players, remove them from the unready list
			and add them to the active player list
			*/

			//Iterate over unready players and add listener for any that are ready
			for (var i = 0; i < this.unreadyPlayers.length; i++) {
				var p = this.unreadyPlayers[i];

				//The player is now ready
				if (p.getPlayerState) {
					this.addEmbedPlayer(p);

					//remove the player from the list
					this.unreadyPlayers.splice(i, 1);
				}
			}
		},
		addEmbedPlayer: function (p) {

			this.addActivePlayer(p);

			/* 
			addEventListener to embedded flash players does not work like standard
			javascript addEventListener. You must pass in the name of a function as a string
			that is in the global scope. Dynamically create a function for each player and
			then add it.
			*/
			window["WT_embedPlayerStateChanged" + p.wtid] = function (state) {
				Webtrends.ytTracker.embedStateChanged(state, p.wtid);
			}
			p.addEventListener("onStateChange", 'WT_embedPlayerStateChanged' + p.wtid);

			window["WT_WT_embedPlayerQualityChanged" + p.wtid] = function () {
				Webtrends.ytTracker.embedQualityChanged(p.wtid);
			}
			p.addEventListener("onPlaybackQualityChange", 'WT_WT_embedPlayerQualityChanged' + p.wtid);

			/*
			p.addEventListener("onStateChange", '(function(state) { return Webtrends.ytTracker.embedStateChanged(state, "' + p.wtid + '"); })');
			p.addEventListener("onPlaybackQualityChange", '(function(state) { return Webtrends.ytTracker.embedQualityChanged("' + p.wtid + '"); })');
			*/
		},
		addIFramePlayer: function (p) {
			if (this.mode === "manual") {
				this.addActivePlayer(p);
				p.addEventListener("onStateChange", Webtrends.ytTracker.iFrameStateChanged);
				p.addEventListener("onPlaybackQualityChange", Webtrends.ytTracker.iFrameQualityChanged);
			}
		},
		addActivePlayer: function (player) {
			player.wtid = this.activePlayerCount;
			player.meta = {};
			player.meta.eventCount = 0;
			player.meta.lastTime = player.getCurrentTime();
			player.meta.lastState = player.getPlayerState();

			this.activePlayers[this.activePlayerCount] = player;
			this.activePlayerCount++;
			this.generateEvent(player, "impressionEvent", null);
		},
		qualityChanged: function (player) {
			//YT API was sometimes sending a quality change event on the initial play.
			//We don't want to track it, so make sure an event other than the initial event
			//has happened in this player.
			if (this.activePlayers[player.wtid].meta.eventCount > 1)
				this.generateEvent(player, "qualityEvent", null);
			Webtrends.ytTracker.activePlayers[player.wtid].meta.lastQualityChange = new Date();
		},
		stateChanged: function (player, newState) {

			/**This will get called by embedded Flash Players which results in few side effects:
			1. You can't debug it (using Chrome at least.) The Flash plugin will crash in Chrome 19 if
			you hit a breakpoint in this function.
			2. If you don't catch them yourself, exceptions will not be apparently. They will trickle up
			to the Flash player.
			*/
			try {
				//Ignore states we don't care about
				if (newState !== YT.PlayerState.PLAYING &&
					newState !== YT.PlayerState.PAUSED &&
					newState !== YT.PlayerState.ENDED)
					return;

				//Hokey way to prevent sending play events that were caused by quality changes
				if (player.meta.lastQualityChange
					&& ((new Date().getTime() - player.meta.lastQualityChange.getTime()) < 1000)
					&& player.meta.lastState !== null
					&& (player.meta.lastState != YT.PlayerState.UNSTARTED && player.meta.lastState != YT.PlayerState.ENDED)) {
					return
				}

				this.generateEvent(player, "actionEvent", newState);
			}
			catch (e) {
				this.errors.push(e);
			}
		},
		generateEvent: function (player, eventType, newState) {

			try {
				var params = {};
				params["WT"] = {};

				params.player = player;
				//State can be funky during quality change events. Don't change it
				if (eventType != "qualityEvent") {
					params.newState = newState;
					params.eventTime = player.getCurrentTime();
				}
				else {
					params.newState = this.activePlayers[player.wtid].meta.lastState;
					params.eventTime = this.activePlayers[player.wtid].meta.lastTime;
				}

				params.eventType = eventType;
				params.quality = player.getPlaybackQuality();
				params["WT"]["WT.yt_tv"] = "10.4.22";

				if (eventType === "actionEvent")
					params.throttle = true
				else
					params.throttle = false;

				if (eventType === "impressionEvent")
					params["WT"]["WT.dl"] = 40;
				else
					params["WT"]["WT.dl"] = 41;

				if (eventType === "actionEvent") {

					//Was this a seek/skip?
					if (player.meta.lastState === newState) {
						params["WT"]["WT.clip_ev"] = "Seek";
						params["WT"]["WT.soc_action"] = "YouTube: Seek";
					}

					else {
						//Is this a play, pause or resume?
						switch (newState) {
							case YT.PlayerState.PLAYING:
								if (player.meta.lastState === YT.PlayerState.PAUSED) {
									params["WT"]["WT.clip_ev"] = "Resume";
									params["WT"]["WT.soc_action"] = "YouTube: Resume";
								}
								else {
									params["WT"]["WT.clip_ev"] = "Play";
									params["WT"]["WT.soc_action"] = "YouTube: Play";
								}
								break;
							case YT.PlayerState.PAUSED:
								params["WT"]["WT.clip_ev"] = "Pause";
								params["WT"]["WT.soc_action"] = "YouTube: Pause";
								break;
							case YT.PlayerState.ENDED:
								params["WT"]["WT.clip_ev"] = "End";
								params["WT"]["WT.soc_action"] = "YouTube: End";
								break;
						}
					}
				}

				if (eventType === "actionEvent" || eventType === "progressEvent" || eventType === "qualityEvent") {
					//Include percentage information for progress events but not state change events unless it is an end
					//Include on plays also, but not skips or resumes
					params["WT"]["WT.clip_secs"] = player.getCurrentTime().toFixed();
					var currentDur = Math.floor((player.getCurrentTime() / player.getDuration()) * 100).toFixed();
					if (eventType === "progressEvent" || newState === YT.PlayerState.ENDED || params["WT"]["WT.clip_ev"] === "Play") {
						params["WT"]["WT.clip_perc"] = Math.floor((currentDur / this.percentageIncrements)) * this.percentageIncrements;
					}
				}

				//Player type (flash or html5)
				params["WT"]["WT.clip_t"] = this.determinePlayerType(player);

				//clip id
				var clipID = this.parseIDFromUrl(player.getVideoUrl());
				params["WT"]["WT.clip_id"] = clipID;

				//Clip Quality
				if (eventType === "qualityEvent")
					params["WT"]["WT.clip_q"] = params.quality;

				var clipName = "unknown";
				try {
					clipName = player.getVideoData().title;
				}
				catch (ex) {
				}

				params["WT"]["WT.clip_n"] = clipName;
				if (eventType === "actionEvent") {
					params["WT"]["WT.soc_content"] = clipName;
				}

				this.sendEvent(params);
			}
			catch (e) {
				this.errors.push(e);
			}
		},
		sendEvent: function (params) {

			//Should I throttle this event?
			//Events from user actions (plays, pauses, etc) will
			//Events from progress checks will not
			var throttle = ((params.throttle === false) ? false : true);

			if (throttle) {
				this.throttledEvents[params.player.wtid] = params;

				var toId = window.setTimeout(
					function () {
						Webtrends.ytTracker.sendThrottledEvent(params);
					},
					this.throttleInterval
				);

				//We have already set a timeout for an event on this player.
				//Since we have another throttled event for this player we
				//know the previous timeout won't do anything. Cancelling it
				if (this.throttleTimeouts[params.player.wtid]) {
					window.clearTimeout(this.throttleTimeouts[params.player.wtid]);
				}

				this.throttleTimeouts[params.player.wtid] = toId;

				return;
			}

			//Update current information about this player
			//This is done here so we only update the meta data
			//with information that was actually sent and not
			//with information that was throttled out.
			this.activePlayers[params.player.wtid].meta.lastState = params.newState;
			this.activePlayers[params.player.wtid].meta.lastTime = params.eventTime;
			this.activePlayers[params.player.wtid].meta.eventCount++;

			var self = this;
			this.tag.dcsMultiTrack({
				args: params["WT"],
				transform: function (tag, options) {
					tag.dcsid = self.dcsid;
				},
				finish: function (tag, options) {
					tag.dcsid = self.maindcsid;
				}
			});
		},
		sendThrottledEvent: function (params) {

			if (this.throttledEvents[params.player.wtid] === params) {
				this.throttledEvents[params.player.wtid] = {};
				params.throttle = false;
				Webtrends.ytTracker.sendEvent(params);
			}
		},
		determinePlayerType: function (player) {
			/***
			There is no obvious way to detect if this is a Flash player or an HTML5 player

			Currently examining the debug text. Flash players appear to include the flash
			version while HTML5 players do not.
			***/

			if (player.getDebugText) {
				var debugText = player.getDebugText();
				if (debugText.indexOf("Flash") !== -1 || debugText.indexOf("flash") !== -1)
					return "Flash";
				else
					return "html5";
			}
			else {
				return "unknown";
			}
		},
		parseIDFromUrl: function (URL) {

			var s = URL.split('/');
			var a = s[s.length - 1].split('?');
			var qps = a[a.length - 1];
			var qpa = qps.split('&');

			var queryParams = [];
			for (var i = 0; i < qpa.length; i++) {
				var t = qpa[i].split("=");
				queryParams[t[0]] = t[1];
			}

			return queryParams["v"] ? queryParams["v"] : "unknown";
		},
		startProgressCheck: function () {

			var pollInterval = 5000;
			window.setTimeout(
				function () {
					Webtrends.ytTracker.checkPlayerProgress(pollInterval);
				},
				pollInterval
			);
		},
		checkPlayerProgress: function (pollInterval) {

			//Iterate over the active players. Compare previous percentage to old percentage
			for (var i = 0; i < this.activePlayers.length; i++) {

				var duration = this.activePlayers[i].getDuration();
				var prevProg = ((this.activePlayers[i].meta.lastTime / duration) * 100).toFixed();
				var currentProg = ((this.activePlayers[i].getCurrentTime() / duration) * 100).toFixed();

				var prevIncrement = Math.floor(prevProg / this.percentageIncrements);
				var currentIncrement = Math.floor(currentProg / this.percentageIncrements);

				if (currentIncrement > prevIncrement) {
					this.generateEvent(this.activePlayers[i], "progressEvent", this.activePlayers[i].getPlayerState());
				}
			}

			//Do it again
			window.setTimeout(
				function () {
					Webtrends.ytTracker.checkPlayerProgress(pollInterval)
				},
				pollInterval
			);
		},
		iFrameStateChanged: function (event) {
			Webtrends.ytTracker.stateChanged(event.target, event.data);
		},
		embedStateChanged: function (state, playerID) {
			Webtrends.ytTracker.stateChanged(Webtrends.ytTracker.activePlayers[playerID], state);
		},
		iFrameQualityChanged: function (event) {
			Webtrends.ytTracker.qualityChanged(event.target);
		},
		embedQualityChanged: function (playerID) {
			Webtrends.ytTracker.qualityChanged(Webtrends.ytTracker.activePlayers[playerID]);
		}
	};

	/*callback for register plugin, which is fired when the main tag is ready for collection to begin.*/
	WTYT_loader = function (tag, plugin) {

		//Add it to the Webtrends object
		Webtrends.ytTracker = new WTYT(tag, plugin);

		//Create a method to allow users to pass in players
		Webtrends.addYTPlayer = function (p) {
			Webtrends.ytTracker.addIFramePlayer(p);
		}

		//We are ready to go, but the YT API js hasn't loaded yet.
		if (!window['YT']) {
			Webtrends.ytTracker.wrapYTCallback();
		}
		//We are ready to go and the YT API has loaded
		else {
			Webtrends.ytTracker.startPlugin();
		}

		//We need to identify when a player becomes ready so
		//so we can attach a listener
		Webtrends.ytTracker.wrapYTPlayerReadyCallback();
	}

	Webtrends.registerPlugin('yt', WTYT_loader);

})(window, window.document);