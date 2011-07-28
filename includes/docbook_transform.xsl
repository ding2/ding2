<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Edited with XML Spy v2007 (http://www.altova.com) -->
<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"
	xmlns:docbook="http://docbook.org/ns/docbook"
	xmlns="http://oss.dbc.dk/ns/opensearch"
>
<xsl:output method="html" indent="yes" />

<!-- ======================================================================================================= -->
<!--       Root Element                                                                                      -->
<!-- ======================================================================================================= -->
<xsl:template match="/">
    <html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
        <link href="docbook.css" rel="stylesheet" type="text/css" />
        <title><xsl:value-of select="/SOAP-ENV:Body/searchResponse/result/searchResult/collection/object/docbook:article/docbook:title"></xsl:value-of></title>
    </head>
    <body>
        <xsl:apply-templates />
    </body>
    </html>
</xsl:template>

<!-- ======================================================================================================= -->
<!--       Empty Elements                                                                                -->
<!-- ======================================================================================================= -->

<xsl:template match="hitCount">
</xsl:template>

<!-- ======================================================================================================= -->
<!--       Docbook Elements                                                                                -->
<!-- ======================================================================================================= -->

<xsl:template match="docbook:article">
	<h1><xsl:value-of select="docbook:title"></xsl:value-of></h1>
    <xsl:apply-templates />	  
</xsl:template>

<xsl:template match="docbook:info">
	<b>Abstract:</b> <xsl:value-of select="docbook:abstract/docbook:para"></xsl:value-of>
	<p/>
	<b>Forfatter:</b> <xsl:value-of select="docbook:author/docbook:personname"></xsl:value-of>
	<p/>
	<b>Emneord:</b> <xsl:apply-templates select="docbook:subjectset"/>
</xsl:template>

<xsl:template match="docbook:subjectset">
	<xsl:apply-templates />
</xsl:template>

<xsl:template match="docbook:subject">
    <xsl:for-each select="docbook:subjectitem">
        <xsl:value-of select="." /><xsl:if test="not(position()=last())">, </xsl:if>
    </xsl:for-each>
</xsl:template>

<xsl:template match="docbook:bibliography">
</xsl:template>

<xsl:template match="docbook:section">
	<h2><xsl:value-of select="docbook:title"></xsl:value-of></h2>
    <xsl:apply-templates />	  
</xsl:template>

<xsl:template match="docbook:section/docbook:title">
</xsl:template>

<xsl:template match="docbook:para/docbook:info">
	<h3><xsl:value-of select="docbook:title"></xsl:value-of></h3>
    <xsl:apply-templates />	  
</xsl:template>

<xsl:template match="docbook:para/docbook:info/docbook:title">
</xsl:template>

</xsl:stylesheet>

