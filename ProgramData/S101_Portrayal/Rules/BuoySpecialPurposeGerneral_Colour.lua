-- BuoySpecialPurposeGerneral_Colour portrayal rules file.

-- Main entry point for feature type.
function BuoySpecialPurposeGerneral_Colour(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType ~= PrimitiveType.Point then
		error(feature.Code .. ' must be of spatial type point')
	end

	-- Colour 12 == magenta

	local colour = { [1] = 12 }

	if feature.colour[1] then
		colour = feature.colour
	end

	local symbol = 'BOYCON01'

	if colour[1] == 1 then
		symbol = 'BOYCAR01'
	elseif (colour[1] == 2) then
		symbol = 'BOYCAR02'
	elseif colour[1] == 3 then
		symbol = 'BOYCAR03'
	elseif colour[1] == 4 then
		symbol = 'BOYCAR04'
	elseif contains(colour[1], { 5, 6, 7 }) then
		symbol = 'BOYBAR01'
	end

	featurePortrayal:AddInstructions('PointInstruction:' .. symbol)
end
