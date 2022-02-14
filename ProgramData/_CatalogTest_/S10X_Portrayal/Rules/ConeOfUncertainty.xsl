<?xml version="1.0" encoding="utf-8"?>

<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" encoding="UTF-8" indent="yes"/>
  <xsl:template match="ConeOfUncertainty[@primitive='Surface']" priority="1">
    <lineInstruction>
      <featureReference>
        <xsl:value-of select="@id"/>
      </featureReference>
      <viewingGroup>26010</viewingGroup>
      <displayPlane>UNDERRADAR</displayPlane>
      <drawingPriority>15</drawingPriority>
      <lineStyleReference reference="ESSARE01"/>
    </lineInstruction>

    <areaInstruction>
      <featureReference>
        <xsl:value-of select="@id"/>
      </featureReference>
      <viewingGroup>31000</viewingGroup>
      <displayPlane>UNDERRADAR</displayPlane>
      <drawingPriority>14</drawingPriority>
      <areaFillReference reference="DIAMOND1"/>
    </areaInstruction>
    
  </xsl:template>

</xsl:transform>


