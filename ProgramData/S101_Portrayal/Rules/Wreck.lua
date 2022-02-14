-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Referenced portrayal rules.
require 'WRECKS05'

-- Wreck main entry point.
function Wreck(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Point and contextParameters.SimplifiedPoints then
		if feature.categoryOfWreck == 3 and feature.valueOfSounding then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:12;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:12;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		elseif feature.categoryOfWreck == 3 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		else
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			end
			WRECKS05(feature, featurePortrayal, contextParameters)
		end
	elseif feature.PrimitiveType == PrimitiveType.Point then
		if feature.categoryOfWreck == 3 and feature.valueOfSounding then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:12;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:12;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		elseif feature.categoryOfWreck == 3 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		else
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			end
			WRECKS05(feature, featurePortrayal, contextParameters)
		end
	elseif feature.PrimitiveType == PrimitiveType.Surface and contextParameters.PlainBoundaries then
		if feature.categoryOfWreck == 3 and feature.valueOfSounding then
			featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:12;DisplayPlane:UnderRADAR')
			featurePortrayal:SimpleLineStyle('dash',0.32,'CHBLK')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
		elseif feature.categoryOfWreck == 3 then
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			featurePortrayal:SimpleLineStyle('dash',0.32,'CHBLK')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
		else
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			WRECKS05(feature, featurePortrayal, contextParameters)
		end
	elseif feature.PrimitiveType == PrimitiveType.Surface then
		if feature.categoryOfWreck == 3 and feature.valueOfSounding then
			featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:12;DisplayPlane:UnderRADAR')
			featurePortrayal:AddInstructions('LineInstruction:NAVARE51')
		elseif feature.categoryOfWreck == 3 then
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			featurePortrayal:AddInstructions('LineInstruction:NAVARE51')
		else
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:12;DisplayPlane:UnderRADAR')
			WRECKS05(feature, featurePortrayal, contextParameters)
		end
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
