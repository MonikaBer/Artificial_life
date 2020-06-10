#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Subjects/Animals/Herbivore.hpp"
#include "../Subjects/Animals/Predator.hpp"
#include "../Subjects/Plants/TypicalPlant.hpp"
#include "../Subjects/SubjectsCollection.hpp"
#include "../helper.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(test_suite_factory)

    BOOST_AUTO_TEST_CASE( testSingletonPattern )
    {
        SubjectsFactory &factory1 = SubjectsFactory::getInstance();
        SubjectsFactory &factory2 = SubjectsFactory::getInstance();
        BOOST_CHECK_EQUAL(&factory1, &factory2);
    }

    BOOST_AUTO_TEST_CASE( testPredatorCreation )
    {
        SubjectsFactory &factory = SubjectsFactory::getInstance();
        Subject *tPred = factory.create(PREDATOR, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        BOOST_CHECK_EQUAL(tPred->getType(), PREDATOR);
        BOOST_CHECK_EQUAL(tPred->getXPosition()%AREA_SIZE, 0);
        BOOST_CHECK_EQUAL(tPred->getYPosition()%AREA_SIZE, 0);
        int predEnergy = static_cast<Animal*>(tPred)->getEnergy();
        int predMaxEnergy = static_cast<Animal*>(tPred)->getMaxEnergy();
        BOOST_CHECK_EQUAL(predEnergy, predMaxEnergy);
    }

    BOOST_AUTO_TEST_CASE( testHerbivoreCreation )
    {
        SubjectsFactory &factory = SubjectsFactory::getInstance();
        Subject *tHerb = factory.create(HERBIVORE, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        BOOST_CHECK_EQUAL(tHerb->getType(), HERBIVORE);
        BOOST_CHECK_EQUAL(tHerb->getXPosition()%AREA_SIZE, 0);
        BOOST_CHECK_EQUAL(tHerb->getYPosition()%AREA_SIZE, 0);
        int herbEnergy = static_cast<Animal*>(tHerb)->getEnergy();
        int herbMaxEnergy = static_cast<Animal*>(tHerb)->getMaxEnergy();
        BOOST_CHECK_EQUAL(herbEnergy, herbMaxEnergy);
    }

    BOOST_AUTO_TEST_CASE( testPlantCreation )
    {
        SubjectsFactory &factory = SubjectsFactory::getInstance();
        Subject *tPlant = factory.create(TYPICAL_PLANT, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        BOOST_CHECK_EQUAL(tPlant->getType(), TYPICAL_PLANT);
        BOOST_CHECK_EQUAL(tPlant->getXPosition()%AREA_SIZE, 0);
        BOOST_CHECK_EQUAL(tPlant->getYPosition()%AREA_SIZE, 0);
    }

BOOST_AUTO_TEST_SUITE_END()