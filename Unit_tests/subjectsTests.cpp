#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include "../Subjects/Animals/Herbivore.hpp"
#include "../Subjects/Animals/Predator.hpp"
#include "../Subjects/Plants/TypicalPlant.hpp"

BOOST_AUTO_TEST_CASE( testSubjectConstructor )
{
//    int x(123), y(887), maxLifeTime(250), viewSize(100);
//    Subject *tSub1 = new Subject(x, y);
//    BOOST_CHECK_EQUAL(tSub1->getXPosition(), x);
//    BOOST_CHECK_EQUAL(tSub1->getYPosition(), y);
//    delete tSub1;
//    tSub1 = nullptr;
//
//    x = 443, y = -5;
//    Subject *tSub2 = new TypicalPlant(x, y);
//    BOOST_CHECK_EQUAL(tSub2->getXPosition(), x);
//    BOOST_CHECK_EQUAL(tSub2->getYPosition(), y);
//    delete tSub2;
//    tSub2 = nullptr;
//
//    x = 1, y = -1;
//    Subject *tSub3 = new Herbivore(x, y, maxLifeTime, viewSize);
//    BOOST_CHECK_EQUAL(tSub3->getXPosition(), x);
//    BOOST_CHECK_EQUAL(tSub3->getYPosition(), y);
//    delete tSub3;
//    tSub3 = nullptr;
//
//    x = 33, y = 1456;
//    Subject *tSub4 = new Predator(x, y, maxLifeTime, viewSize);
//    BOOST_CHECK_EQUAL(tSub4->getXPosition(), x);
//    BOOST_CHECK_EQUAL(tSub4->getYPosition(), y);
//    delete tSub4;
//    tSub4 = nullptr;
}

BOOST_AUTO_TEST_CASE( testAnimalMove )
{
    /*
    int x(40), y(40), maxLifeTime(250), viewSize(100);
    Herbivore *tSub1 = new Herbivore(x, y, maxLifeTime, viewSize);
    int foodX(50), foodY(50);
    BOOST_CHECK(tSub1->lookAround(foodX, foodY, 0));   // 0 is food, not partner
    int leapsNumber = tSub1->move(foodX, foodY);
    //BOOST_CHECK_NOT_EQUAL(leapsNumber, 0);
    //BOOST_CHECK_NOT_EQUAL(tSub1->getXPosition(), x);
    //BOOST_CHECK_NOT_EQUAL(tSub1->getYPosition(), y);

    delete tSub1;
    tSub1 = nullptr;
    */
}

BOOST_AUTO_TEST_CASE( testAnimalSleep )
{

}

BOOST_AUTO_TEST_CASE( testAnimalReproduce )
{

}

BOOST_AUTO_TEST_CASE( testAnimalLookAround )
{

}

BOOST_AUTO_TEST_CASE( testUpdateParameters )
{

}

BOOST_AUTO_TEST_CASE( testHerbivoreEat )
{

}

BOOST_AUTO_TEST_CASE( testPredatorEat )
{

}