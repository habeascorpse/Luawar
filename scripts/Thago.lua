function loadResources()
	 print("Loading Person thago.lua Resources...")
	-- Hero State
	ForceX = 140
	life = 400
	posX = 0
	posY = 0
	weight = 120
	friction = 0.8
	density = 5
	direction  = 6

	-- Hero Images
	walkingRightA ="../images/thago/d1.png"
	walkingRightB ="../images/thago/d2.png"
	walkingRightC = "../images/thago/d3.png"
	walkingRightD = "../images/thago/d4.png"
	walkingLeftA = "../images/thago/e1.png"
	walkingLeftB = "../images/thago/e2.png"
	walkingLeftC = "../images/thago/e3.png"
	walkingLeftD = "../images/thago/e4.png"

	jumpingRightA = "../images/thago/d7.png"
	jumpingRightB ="../images/thago/d3.png"

	jumpingLeftA ="../images/thago/e7.png"
	jumpingLeftB ="../images/thago/e3.png"
	
	attackRightA ="../images/thago/d5.png"
	attackRightB ="../images/thago/d6.png"
	attackLeftA ="../images/thago/e5.png"
	attackLeftB ="../images/thago/e6.png"


	tJumping = 100
	tWalking = 120
	tAttack = 100
	print("Completed!")

end


loadResources()
