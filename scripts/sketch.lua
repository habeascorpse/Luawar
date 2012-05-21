function loadResources()
	 print("Loading Person sketch.lua Resources...")
	-- Hero State
	ForceX = 100
	life = 200
	posX = 0
	posY = 0
	weight = 80
	friction = 0.8
	density = 1
	direction  = 6

	-- Hero Images
	walkingRightA ="../images/sketch/d1.png"
	walkingRightB ="../images/sketch/d2.png"
	walkingRightC = "../images/sketch/d3.png"
	walkingRightD = "../images/sketch/d4.png"
	walkingLeftA = "../images/sketch/e1.png"
	walkingLeftB = "../images/sketch/e2.png"
	walkingLeftC = "../images/sketch/e3.png"
	walkingLeftD = "../images/sketch/e4.png"

	jumpingRightA = "../images/sketch/d7.png"
	jumpingRightB ="../images/sketch/d3.png"

	jumpingLeftA ="../images/sketch/e7.png"
	jumpingLeftB ="../images/sketch/e3.png"
	
	attackRightA ="../images/sketch/d5.png"
	attackRightB ="../images/sketch/d6.png"
	attackLeftA ="../images/sketch/e5.png"
	attackLeftB ="../images/sketch/e6.png"


	tJumping = 100
	tWalking = 140
	tAttack = 100
	print("Completed!")

end


loadResources()
