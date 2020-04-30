#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include "../Subjects/Herbivore.hpp"
#include "../Subjects/Plant.hpp"

BOOST_AUTO_TEST_CASE( testSubjectConstructor )
{
    int x(123), y(887);
    Subject *tSub1 = new Subject(x, y);
    BOOST_CHECK(tSub1->getXPosition() == x && tSub1->getYPosition() == y);
    delete tSub1;
    tSub1 = nullptr;

    x = 443, y=-5;
    Subject *tSub2 = new Plant(x, y);
    BOOST_CHECK(tSub2->getXPosition() == x && tSub2->getYPosition() == y);
    delete tSub2;
    tSub2 = nullptr;

    x = 1, y = -1;
    Subject *tSub3 = new Herbivore(x, y);
    BOOST_CHECK(tSub3->getXPosition() == x && tSub3->getYPosition() == y);
    delete tSub3;
    tSub3 = nullptr;
    /*
    x = 33, y = 1456;
    Subject *tSub4 = new Predator(x, y);
    BOOST_CHECK(tSub4->getYPosition() == x && tSub4->getYPosition() == y);
    delete tSub4;
    tSub4 = nullptr;
    */
}

BOOST_AUTO_TEST_CASE( testMoving )
{
    int x(40), y(40);
    Herbivore *tSub1 = new Herbivore(x, y);
    tSub1->setDirection(2);
    tSub1->move();
    BOOST_CHECK(tSub1->getXPosition()!=x && tSub1->getYPosition()!=y);
    delete tSub1;
    tSub1 = nullptr;
}