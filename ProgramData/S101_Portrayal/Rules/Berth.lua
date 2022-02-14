-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Berth main entry point.
function Berth(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Point then
		-- Simplified and paper chart points use the same symbolization
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:32440;DrawingPriority:15;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:32440;DrawingPriority:15;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:AddInstructions('PointInstruction:BRTHNO01')
		featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'Nr %s') .. ',29,8')
	elseif feature.PrimitiveType == PrimitiveType.Curve then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:32440;DrawingPriority:15;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:32440;DrawingPriority:15;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:SimpleLineStyle('solid',0.96,'CHGRD')
		featurePortrayal:AddInstructions('LineInstruction:_simple_')
		featurePortrayal:AddInstructions('PointInstruction:BRTHNO01')
		featurePortrayal:AddInstructions('LocalOffset:0,0;TextAlignHorizontal:Center;TextAlignVertical:Center;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'Nr %s') .. ',29,8')
	elseif feature.PrimitiveType == PrimitiveType.Surface then
		-- Plain and symbolized boundaries use the same symbolization
		featurePortrayal:AddInstructions('ViewingGroup:32440;DrawingPriority:9;DisplayPlane:UnderRADAR')
		featurePortrayal:AddInstructions('PointInstruction:BRTHNO01')
		featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'Nr %s') .. ',29,8')
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
