-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Referenced portrayal rules.
require 'TOPMAR01'

-- Beacon Isolated Danger main entry point.
function BeaconIsolatedDanger(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Point and contextParameters.SimplifiedPoints then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:AddInstructions('PointInstruction:BCNISD21')
		if feature.featureName[1] and feature.featureName[1].name then
			featurePortrayal:AddInstructions('LocalOffset:-3.51,3.51;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
		end
	elseif feature.PrimitiveType == PrimitiveType.Point then
		if feature.beaconShape == 1 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:BCNSTK02')
			if feature.featureName[1] and feature.featureName[1].name then
				featurePortrayal:AddInstructions('LocalOffset:-3.51,3.51;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
			end
			TOPMAR01(feature, featurePortrayal, contextParameters, false)
		elseif feature.beaconShape == 3 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:BCNTOW01')
			if feature.featureName[1] and feature.featureName[1].name then
				featurePortrayal:AddInstructions('LocalOffset:-3.51,7.02;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
			end
			TOPMAR01(feature, featurePortrayal, contextParameters, false)
		elseif contains(11, feature.natureOfConstruction) then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:BCNLTC01')
			if feature.featureName[1] and feature.featureName[1].name then
				featurePortrayal:AddInstructions('LocalOffset:-3.51,7.02;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
			end
			TOPMAR01(feature, featurePortrayal, contextParameters, false)
		elseif feature.beaconShape == 5 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:BCNGEN01')
			if feature.featureName[1] and feature.featureName[1].name then
				featurePortrayal:AddInstructions('LocalOffset:-3.51,7.02;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
			end
			TOPMAR01(feature, featurePortrayal, contextParameters, false)
		elseif feature.beaconShape == 7 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:BCNGEN01')
			if feature.featureName[1] and feature.featureName[1].name then
				featurePortrayal:AddInstructions('LocalOffset:-3.51,7.02;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
			end
			TOPMAR01(feature, featurePortrayal, contextParameters, false)
		else
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:27020;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:BCNGEN03')
			if feature.featureName[1] and feature.featureName[1].name then
				featurePortrayal:AddInstructions('LocalOffset:-3.51,3.51;TextAlignHorizontal:End;FontSize:10;TextInstruction:' .. EncodeString(GetFeatureName(feature, contextParameters), 'bn %s') .. ',21,8')
			end
			TOPMAR01(feature, featurePortrayal, contextParameters, false)
		end
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
