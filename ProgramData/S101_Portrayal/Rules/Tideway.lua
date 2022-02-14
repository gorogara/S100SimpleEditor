-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Tideway main entry point.
function Tideway(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Curve then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:32070;DrawingPriority:9;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:32070;DrawingPriority:9;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:SimpleLineStyle('solid',0.32,'CHGRF')
		featurePortrayal:AddInstructions('LineInstruction:_simple_')
	elseif feature.PrimitiveType == PrimitiveType.Surface then
		-- Plain and symbolized boundaries use the same symbolization
		featurePortrayal:AddInstructions('ViewingGroup:32070;DrawingPriority:21;DisplayPlane:UnderRADAR')
		featurePortrayal:SimpleLineStyle('dash',0.32,'CHGRF')
		featurePortrayal:AddInstructions('LineInstruction:_simple_')
		if feature.featureName[1] and feature.featureName[1].name then
			featurePortrayal:AddInstructions('LocalOffset:0,0;TextAlignHorizontal:Center;TextAlignVertical:Center;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters)) .. ',25,8')
		end
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
