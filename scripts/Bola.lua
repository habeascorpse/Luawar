function loadResources()
	 print("olá")
	-- Hero State
	ForceX = 40
	life = 100
	posX = 0
	posY = 0
	weight = 10
	friction = 0.1
	density = 0
	direction  = 6

	-- Hero Images
	walkingRightA ="../images/bola/b1.png"
	walkingRightB ="../images/bola/b2.png"
	walkingRightC = "../images/bola/b3.png"
	walkingRightD = "../images/bola/b4.png"
	walkingLeftA = "../images/bola/b1.png"
	walkingLeftB = "../images/bola/b2.png"
	walkingLeftC = "../images/bola/b3.png"
	walkingLeftD = "../images/bola/b4.png"

	jumpingRightA = "../images/bola/b1.png"
	jumpingRightB ="../images/bola/b2.png"

	jumpingLeftA ="../images/bola/b3.png"
	jumpingLeftB ="../images/bola/b4.png"

	tJumping = 100
	tWalking = 150
	tAttack = 100

end

function processAI()
	local a = person:getPosX()
	local b = ia1:getPosX()
	local c = ia2:getPosX()


	if ia1:getDirection() == 5 then
		ia1:movLeft(45)
		if b <= 10   then
			ia1:setDirection(4)
		end		
	else
		ia1:movRight(45)
		if b >=260 then
			ia1:setDirection(5)
		end
	end

end


loadResources()
