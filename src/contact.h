#ifndef CONTACT_H_INCLUDED
#define CONTACT_H_INCLUDED
#include "defs.h"
#include "objectai.h"
#include "bullet.h"
#include <Box2D.h>
#include <string>


using namespace std;

class ContactListener : public b2ContactListener
{
public:
	void Add(const b2ContactPoint* point)
    {

        // handle add point
        if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0005) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0005)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          if (point->shape1->GetBody()->GetUserData() != NULL) {
            AI::ObjectAI* temp = (AI::ObjectAI *)point->shape1->GetBody()->GetUserData();
            Bullet * tempBullet = (Bullet *)point->shape2->GetBody()->GetUserData();
            tempBullet->running = 0;
            temp->decreaseLife(10);
            if (temp->getPosX() >= tempBullet->body->GetPosition().x)
              temp->movRight(400);
            else
              temp->movLeft(400);
          }

        }
        if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0004) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0005)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          Bullet * tempBullet = (Bullet *)point->shape2->GetBody()->GetUserData();
          tempBullet->running = 0;
        }
        if ((point->shape1->GetFilterData().categoryBits  == 0x0002)
        &&(point->shape1->GetFilterData().maskBits  == 0x0002) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          Person *person = (Person *)point->shape1->GetBody()->GetUserData();
          AI::ObjectAI *ia = (AI::ObjectAI *) point->shape2->GetBody()->GetUserData();
          ia->colide = true;
          if (ia->timeAttackIA >= 500) {
              ia->timeAttackIA = 0;
              if (person->getPosX() > ia->getPosX()) {
                if ((ia->getDirection() == ACT_MV_RIGHT) && (ia->isAttack())) {
                  person->decreaseLife(10);
                }
              }
              else {
                if ((ia->getDirection() == ACT_MV_LEFT) && (ia->isAttack())) {
                  person->decreaseLife(10);
                }
              }
          }
        }
        // Contact with Person and map
        if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0004) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0002)
        &&(point->shape2->GetFilterData().maskBits  == 0x0002) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          Person* person = (Person *) point->shape2->GetBody()->GetUserData();
          //Colision Left
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x <= (person->getPosX() + 2))) {
            person->colideLeft = true;
          }
          else
            person->colideLeft = false;
          //Colision Right
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x > (person->getPosX() + person->sizexImg - 2))) {
            person->colideRight = true;
          }
          else
            person->colideRight = false;
        }
      // Contact with Person and map
        if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0004) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          Person* person = (Person *) point->shape2->GetBody()->GetUserData();
          //Colision Left
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x <= (person->getPosX() + 2))) {
            person->colideLeft = true;
          }
          else
            person->colideLeft = false;
          //Colision Right
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x > (person->getPosX() + person->sizexImg - 2))) {
            person->colideRight = true;
          }
          else
            person->colideRight = false;
        }
    }

	void Persist(const b2ContactPoint* point)
    {
        if ((point->shape1->GetFilterData().categoryBits  == 0x0002)
        &&(point->shape1->GetFilterData().maskBits  == 0x0002) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          Person *person = (Person *)point->shape1->GetBody()->GetUserData();
          AI::ObjectAI *ia = (AI::ObjectAI *) point->shape2->GetBody()->GetUserData();
          ia->colide = true;
          if (ia->timeAttackIA >= 1000) {
              ia->timeAttackIA = 0;
              if (person->getPosX() > ia->getPosX()) {
                if ((ia->getDirection() == ACT_MV_RIGHT) && (ia->isAttack())) {
                  person->decreaseLife(10);
                }
              }
              else {
                if ((ia->getDirection() == ACT_MV_LEFT) && (ia->isAttack())) {
                  person->decreaseLife(10);
                }
              }
          }
        }
        // Contact with Person and map

        if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0004) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0002)
        &&(point->shape2->GetFilterData().maskBits  == 0x0002) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          //Colision Left
          Person* person = (Person *) point->shape2->GetBody()->GetUserData();
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x <= (person->getPosX() + 2))) {
            person->colideLeft = true;
          }
          else
            person->colideLeft = false;
          //Colision Right
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x > (person->getPosX() + person->sizexImg - 2))) {
            person->colideRight = true;
          }
          else
            person->colideRight = false;
        }
         if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0004) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          //Colision Left
          Person* person = (Person *) point->shape2->GetBody()->GetUserData();
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x <= (person->getPosX() + 2))) {
            person->colideLeft = true;
          }
          else
            person->colideLeft = false;
          //Colision Right
          if ((point->position.y > (person->getPosY() +5)) && (point->position.y < (person->getPosY() + person->sizeyImg - 5))
           && (point->position.x > (person->getPosX() + person->sizexImg - 2))) {
            person->colideRight = true;
          }
          else
            person->colideRight = false;
        }
        if ((point->shape1->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape1->GetFilterData().maskBits  == 0x0004) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0005)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          Bullet * tempBullet = (Bullet *)point->shape2->GetBody()->GetUserData();
          tempBullet->running = 0;
        }

    }

	void Remove(const b2ContactPoint* point)
    {
        // handle remove point
        if ((point->shape1->GetFilterData().categoryBits  == 0x0002)
        &&(point->shape1->GetFilterData().maskBits  == 0x0002) &&
        (point->shape1->GetFilterData().groupIndex==1) &&
        (point->shape2->GetFilterData().categoryBits  == 0x0004)
        &&(point->shape2->GetFilterData().maskBits  == 0x0005) &&
        (point->shape2->GetFilterData().groupIndex==1))
        {
          AI::ObjectAI *ia = (AI::ObjectAI *) point->shape2->GetBody()->GetUserData();
          ia->colide = false;
        }
    }

    void Result(const b2ContactResult* point)
    {
        // handle results
    }
};


#endif // CONTACT_H_INCLUDED
