
if (((ia:getPosX() - person:getPosX()) < (DF_WIDTH/2)) and ((ia:getPosX() - person:getPosX()) > 0)) or (((person:getPosX() - ia:getPosX()) < (DF_WIDTH/2)) and ((person:getPosX() - ia:getPosX()) > 0)) then
  if (ia.colide == true) then
        ia:attack(true)
  end
  if ia:getLife() <= 40 then
    ia:jump()
    if person:getDirection() ~= ia:getDirection() then
      if ia:getDirection() == 5 then
        ia:setDirection(4)
        ia:setMov()
      else
        ia:setDirection(5)
        ia:setMov()
      end
    end

  else
      if (ia.colide == true) then
        ia:attack(true)
      else
        if (ia:getPosX() > person:getPosX()) then
          ia:setDirection(5)
          ia:setMov()
        else
          ia:setDirection(4)
          ia:setMov()
        end
      end
  end
end
