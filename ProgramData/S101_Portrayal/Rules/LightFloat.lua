-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Referenced portrayal rules.
require 'TOPMAR01'

-- Light float main entry point.
function LightFloat(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Point and contextParameters.SimplifiedPoints then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:27010;DrawingPriority:24;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:27010;DrawingPriority:24;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:AddInstructions('PointInstruction:LITFLT02')
		if feature.featureName[1] and feature.featureName[1].name then
			featurePortrayal:AddInstructions('LocalOffset:-3.51,3.51;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'by %s') .. ',21,8')
		end
	elseif feature.PrimitiveType == PrimitiveType.Point then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:27010;DrawingPriority:24;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:27010;DrawingPriority:24;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:AddInstructions('PointInstruction:LITFLT01')
		if feature.featureName[1] and feature.featureName[1].name then
			featurePortrayal:AddInstructions('LocalOffset:-3.51,3.51;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'by %s') .. ',21,8')
		end
		TOPMAR01(feature, featurePortrayal, contextParameters, true)
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
