// For some reason resetting will not work if run to early. Perhaps the
// persisted store is not quite ready. Consequently we have to wait a bit.
setTimeout(() => window.ddbReact.reset(), 500);
