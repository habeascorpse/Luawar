print "bacana"
local person = Person()
local i = person:getLife()
print (i)
person:setLife(15)
i = person:getLife()
print ("agora é",i)
person:setPosX(32)
print (person:getPosX())