<?xml version="1.0" encoding="utf-8" ?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output indent="yes" version="1.0"/>

  <xsl:template name="differentDisplayByScaleTemplate">
    <xsl:param name="minScale" select="0"/>
    <xsl:param name="maxScale" select="0"/>
    <xsl:param name="featureReference"></xsl:param>
    <xsl:param name="viewingGroup"></xsl:param>
    <xsl:param name="displayPlane"></xsl:param>
    <xsl:param name="drawingPriority"></xsl:param>

    <!-- 1번째 심볼 범위 Scale -->
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
      <scaleMinimum>0</scaleMinimum>
      <scaleMaximum>
        <xsl:value-of select="$minScale"/>
      </scaleMaximum>
      <xsl:element name="symbol">
        <xsl:attribute name="reference">ACHARE51_D</xsl:attribute>
      </xsl:element>
    </pointInstruction>

    <!-- 2번째 심볼 범위 Scale -->
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
      <scaleMinimum>
        <xsl:value-of select="$minScale"/>
      </scaleMinimum>
      <scaleMaximum>
        <xsl:value-of select="$maxScale"/>
      </scaleMaximum>
      <xsl:element name="symbol">
        <xsl:attribute name="reference">ACHARE51</xsl:attribute>
      </xsl:element>
    </pointInstruction>

    <!-- 3번째 심볼 범위 Scale -->
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
      <scaleMinimum>
        <xsl:value-of select="$maxScale"/>
      </scaleMinimum>
      <scaleMaximum>0</scaleMaximum>
      <xsl:element name="symbol">
        <xsl:attribute name="reference">ACHARE51_U</xsl:attribute>
      </xsl:element>
    </pointInstruction>

  </xsl:template>
  
</xsl:transform>