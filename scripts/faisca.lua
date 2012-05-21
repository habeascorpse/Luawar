

for time = 1, plua:getNum(), 1 do

    plua:setX(time,plua:getX(time) + plua:getVelX(time))
    plua:setY(time,plua:getY(time) + plua:getVelY(time))
end
