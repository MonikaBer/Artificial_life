#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include "../Subjects/Herbivore.hpp"
#include "../Subjects/Predator.hpp"
#include "../Subjects/TypicalPlant.hpp"

BOOST_AUTO_TEST_CASE( testSubjectConstructor )
{
    int x(123), y(887), maxLifeTime(250), viewSize(100);
    // Subject *tSub1 = new Subject(x, y);
    // BOOST_CHECK(tSub1->getXPosition() == x && tSub1->getYPosition() == y);
    // delete tSub1;
    // tSub1 = nullptr;

    x = 443, y = -5;
    Subject *tSub2 = new TypicalPlant(x, y);
    BOOST_CHECK(tSub2->getXPosition() == x && tSub2->getYPosition() == y);
    delete tSub2;
    tSub2 = nullptr;

    // x = 1, y = -1;
    // Subject *tSub3 = new Herbivore(x, y, maxLifeTime, viewSize);
    // BOOST_CHECK(tSub3->getXPosition() == x && tSub3->getYPosition() == y);
    // delete tSub3;
    // tSub3 = nullptr;
    
    // x = 33, y = 1456;
    // Subject *tSub4 = new Predator(x, y, maxLifeTime, viewSize);
    // BOOST_CHECK(tSub4->getYPosition() == x && tSub4->getYPosition() == y);
    // delete tSub4;
    // tSub4 = nullptr;
}

// BOOST_AUTO_TEST_CASE( testMoving )
// {
//     int x(40), y(40), maxLifeTime(250), viewSize(100);
//     Herbivore *tSub1 = new Herbivore(x, y, maxLifeTime, viewSize);
//     int foodX = 50, foodY = 50;
//     BOOST_CHECK(tSub1->lookAround(foodX, foodY, 0));   // 0 is food, not partner
//     int leapsNumber = tSub1->move(foodX, foodY);
//     BOOST_CHECK(leapsNumber != 0 && tSub1->getXPosition()!=x && tSub1->getYPosition()!=y);

//     delete tSub1;
//     tSub1 = nullptr;
// }