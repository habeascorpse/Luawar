-- movimentação

	if ia.colide == true  then
        print ("está colidido")
		if person:getPosX() > ia:getPosX() then
			ia:setDirection(5)
			ia:attack(true)
		else
			ia:setDirection(4)
			ia:attack(true)
		end
	end

	if ia:getDirection() == 5 then
		ia:setMov()
		if (ia:getPosX() <= 60) or (ia:getSpeedX() == 0)   then
			ia:setDirection(4)
		end

	else
		ia:setMov()
		if (ia:getPosX() >=260) or (ia:getSpeedX() == 0) then
			ia:setDirection(5)
		end
	end

--print (DF_HEIGHT)


