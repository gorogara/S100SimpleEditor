<?xml version="1.0" encoding="utf-8" ?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output indent="yes" version="1.0"/>

  <xsl:template name="scaledFeatureTemplate">
    <xsl:param name="minScale" select="0"/>
    <xsl:param name="maxScale" select="0"/>
    <xsl:param name="featureReference"></xsl:param>
    <xsl:param name="viewingGroup"></xsl:param>
    <xsl:param name="displayPlane"></xsl:param>
    <xsl:param name="drawingPriority"></xsl:param>

    <xsl:choose>
      <xsl:when test="scaleMinimum > $CURRENT_SCALE">
        <pointInstruction>
          <featureReference>
            <xsl:value-of select="@id"/>
          </featureReference>
          <viewingGroup>
            <xsl:value-of select="$viewingGroup"/>
          </viewingGroup>
          <displayPlane>
            <xsl:value-of select="$displayPlane"/>
          </displayPlane>
          <drawingPriority>
            <xsl:value-of select="$drawingPriority"/>
          </drawingPriority>
          <xsl:element name="symbol">
            <xsl:attribute name="reference">ACHARE51_D</xsl:attribute>
          </xsl:element>
        </pointInstruction>
      </xsl:when>
      <xsl:when test="$CURRENT_SCALE > scaleMaximum">
        <pointInstruction>
          <featureReference>
            <xsl:value-of select="@id"/>
          </featureReference>
          <viewingGroup>
            <xsl:value-of select="$viewingGroup"/>
          </viewingGroup>
          <displayPlane>
            <xsl:value-of select="$displayPlane"/>
          </displayPlane>
          <drawingPriority>
            <xsl:value-of select="$drawingPriority"/>
          </drawingPriority>
          <xsl:element name="symbol">
            <xsl:attribute name="reference">ACHARE51_U</xsl:attribute>
          </xsl:element>
        </pointInstruction>
      </xsl:when>
      <xsl:otherwise>
        <pointInstruction>
          <featureReference>
            <xsl:value-of select="@id"/>
          </featureReference>
          <viewingGroup>
            <xsl:value-of select="$viewingGroup"/>
          </viewingGroup>
          <displayPlane>
            <xsl:value-of select="$displayPlane"/>
          </displayPlane>
          <drawingPriority>
            <xsl:value-of select="$drawingPriority"/>
          </drawingPriority>
          <xsl:element name="symbol">
            <xsl:attribute name="reference">ACHARE51</xsl:attribute>
          </xsl:element>
        </pointInstruction>
      </xsl:otherwise>
    </xsl:choose>

  </xsl:template>
  
</xsl:transform>