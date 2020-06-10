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

    BOOST_AUTO_TEST_CASE( testPlantCreation )
    {
        SubjectsFactory &factory = SubjectsFactory::getInstance();
        Subject *tPred = factory.create(PREDATOR, WINDOW_WIDTH/AREA_SIZE, WINDOW_HEIGHT/AREA_SIZE, AREA_SIZE, MAX_LIFE_TIME, VIEW_SIZE);
        BOOST_CHECK_EQUAL(tPred->getType(), PREDATOR);
    }

BOOST_AUTO_TEST_SUITE_END()