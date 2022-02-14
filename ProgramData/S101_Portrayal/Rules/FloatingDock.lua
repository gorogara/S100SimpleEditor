-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Floating dock main entry point.
function FloatingDock(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Curve then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:12410;DrawingPriority:15;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:12410;DrawingPriority:15;DisplayPlane:UnderRADAR')
		end
		featurePortrayal:SimpleLineStyle('solid',0.96,'CSTLN')
		featurePortrayal:AddInstructions('LineInstruction:_simple_')
	elseif feature.PrimitiveType == PrimitiveType.Surface then
		-- Plain and symbolized boundaries use the same symbolization
		featurePortrayal:AddInstructions('ViewingGroup:12410;DrawingPriority:6;DisplayPlane:UnderRADAR')
		featurePortrayal:AddInstructions('ColorFill:CHBRN')
		featurePortrayal:SimpleLineStyle('solid',0.64,'CSTLN')
		featurePortrayal:AddInstructions('LineInstruction:_simple_')
	elseif feature.PrimitiveType == PrimitiveType.Point then
		--TODO: Determine S-101 portrayal for FloatingDock point feature.
		featurePortrayal:AddInstructions('ViewingGroup:21010;DrawingPriority:15;PointInstruction:testPCB')
		Debug.Trace('Warning: S-52 does not define portrayal for FloatingDock point features.')
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
