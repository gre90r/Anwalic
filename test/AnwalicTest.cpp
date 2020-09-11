/**
 * all test cases for whole program
 * 
 * !!! KEEP ALL TEST CASES HERE !!!
 * re:running all tests is easy that way
 *
 * HOW TO BUILD with Visual Studio:
 * --------------------------------
 * -> Anwalic Solution has to create .lib file with the build
 *      -> right click on solution Anwalic -> Properties -> Configuration Properties -> General
 *          -> Configuration Type = Static Library (.lib)
 *              -> don't forget to set it back to Application (.exe) when you want to run Anwalic
 * -> still error?
 *      -> set Solution Configuration to Debug
 *      -> is it still in Release Mode?
 * 
 * @author gre90r
 * @created December 28th, 2016
 */

#include "gtest/gtest.h"
#include "../src/StringUtils.h"
#include "../src/globals.h"
#include "../src/memory.h"
#include "../src/anime.h"
#include "../src/animelist.h"


/****************/
/* Anime::Anime */
/****************/
TEST( Anime_Constructor, noArguments )
{
    Anime anime = Anime();
    ASSERT_EQ( anime.getName(), "" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), MAX_NUMBER_EPISODES );
    ASSERT_EQ( anime.getUrl(), "" );
}
TEST( Anime_Constructor, nameOnlyInUppercase )
{
    Anime anime = Anime( "Clannad" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), MAX_NUMBER_EPISODES );
    ASSERT_EQ( anime.getUrl(), "" );
}
TEST( Anime_Constructor, nameOnlyInLowercase )
{
    Anime anime = Anime( "clannad" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), MAX_NUMBER_EPISODES );
    ASSERT_EQ( anime.getUrl(), "" );
}
TEST( Anime_Constructor, nameAndCurrentEpisde )
{
    Anime anime = Anime( "Clannad", 5 );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 5 );
    ASSERT_EQ( anime.getTotalEpisodes(), MAX_NUMBER_EPISODES );
    ASSERT_EQ( anime.getUrl(), "" );
}
TEST( Anime_Constructor, onlyUrlMissing )
{
    Anime anime = Anime( "Clannad", 5, 12 );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 5 );
    ASSERT_EQ( anime.getTotalEpisodes(), 12 );
    ASSERT_EQ( anime.getUrl(), "" );
}
TEST( Anime_Constructor, fullConstructor )
{
    Anime anime = Anime( "Clannad", 5, 12, "http://www.google.de" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 5 );
    ASSERT_EQ( anime.getTotalEpisodes(), 12 );
    ASSERT_EQ( anime.getUrl(), "http://www.google.de" );
}
TEST( Anime_Constructor, httpsUrl )
{
    Anime anime = Anime( "Clannad", 5, 12, "https://www.google.de" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 5 );
    ASSERT_EQ( anime.getTotalEpisodes(), 12 );
    ASSERT_EQ( anime.getUrl(), "https://www.google.de" );
}
TEST( Anime_Constructor, invalidCurrentEpisode )
{
    Anime anime = Anime( "Clannad", -2, 12, "https://www.google.de" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), 12 );
    ASSERT_EQ( anime.getUrl(), "https://www.google.de" );
}
TEST( Anime_Constructor, invalidTotalEpisode )
{
    Anime anime = Anime( "Clannad", 1, -5, "https://www.google.de" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), MAX_NUMBER_EPISODES );
    ASSERT_EQ( anime.getUrl(), "https://www.google.de" );
}
TEST( Anime_Constructor, invalidUrl )
{
    Anime anime = Anime( "Clannad", 1, 12, "sdfhsadfhsadfh" );
    ASSERT_EQ( anime.getName(), "Clannad" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), 12 );
    ASSERT_EQ( anime.getUrl(), "" );
}
TEST( Anime_Constructor, invalidAnimeName )
{
    Anime anime = Anime( "Clannad (After|Story)", 1, 12, "http://www.google.de" );
    ASSERT_EQ( anime.getName(), "Clannad [After/Story]" );
    ASSERT_EQ( anime.getCurrentEpisode(), 1 );
    ASSERT_EQ( anime.getTotalEpisodes(), 12 );
    ASSERT_EQ( anime.getUrl(), "http://www.google.de" );
}
TEST( Anime_Constructor, animeNameTooLong )
{
    std::string animeName;
    for ( int i = 0; i < 2000; i++ ) // 2000 characters
    {
        animeName += "a";
    }
    Anime anime = Anime( animeName );
    ASSERT_EQ( anime.getName().size(), MAX_ANIME_NAME_LENGTH );
}

/******************/
/* Anime::getName */
/******************/
TEST( Anime_getName, getName )
{
    Anime anime = Anime( "Clannad" );
    ASSERT_EQ( "Clannad", anime.getName() );
}

/*********************/
/* Anime::getCurrentEpisode */
/*********************/
TEST( Anime_getEpisode, getEpisode )
{
    Anime anime = Anime( "Clannad", 5 );
    ASSERT_EQ( 5, anime.getCurrentEpisode() );
}

/***************************/
/* Anime::getTotalEpisodes */
/***************************/
TEST( Anime_getTotalEpisodes, getTotalEpisodes )
{
    Anime anime = Anime( "Clannad", 1, 7 );
    ASSERT_EQ( 7, anime.getTotalEpisodes() );
}

/*****************/
/* Anime::getUrl */
/*****************/
TEST( Anime_getUrl, getUrl )
{
    Anime anime = Anime( "Clannad", 1, 7, "http://www.google.de" );
    ASSERT_EQ( "http://www.google.de", anime.getUrl() );
}

/******************/
/* Anime::setName */
/******************/
TEST( Anime_setName, validName1 )
{
    Anime anime = Anime();
    anime.setName( "Clannad" );
    ASSERT_EQ( "Clannad", anime.getName() );
}
TEST( Anime_setName, validName2 )
{
    Anime anime = Anime();
    anime.setName( "Fullmetal Alchemist: Brotherhood [Ger Dub]" );
    ASSERT_EQ( "Fullmetal Alchemist: Brotherhood [Ger Dub]", anime.getName() );
}
TEST( Anime_setName, invalidName1 )
{
    Anime anime = Anime();
    anime.setName( "clannad" );
    ASSERT_EQ( "Clannad", anime.getName() );
}
TEST( Anime_setName, invalidName2 )
{
    Anime anime = Anime();
    anime.setName( "Clannad (After Story)" );
    ASSERT_EQ( "Clannad [After Story]", anime.getName() );
}
TEST( Anime_setName, invalidName3 )
{
    Anime anime = Anime();
    anime.setName( "Max | Pain" );
    ASSERT_EQ( "Max / Pain", anime.getName() );
}
TEST( Anime_setName, valdiNameNeedsTrim1 )
{
    Anime anime = Anime();
    anime.setName( "Clannad   " );
    ASSERT_EQ( "Clannad", anime.getName() );
}
TEST( Anime_setName, valdiNameNeedsTrim2 )
{
    Anime anime = Anime();
    anime.setName( "   Clannad" );
    ASSERT_EQ( "Clannad", anime.getName() );
}
TEST( Anime_setName, valdiNameNeedsTrim3 )
{
    Anime anime = Anime();
    anime.setName( "   Clannad   " );
    ASSERT_EQ( "Clannad", anime.getName() );
}

/*********************/
/* Anime::setEpisode */
/*********************/
TEST( Anime_setEpisode, valid1 )
{
    Anime anime = Anime();
    anime.setEpisode( 5 );
    ASSERT_EQ( 5, anime.getCurrentEpisode() );
}
TEST( Anime_setEpisode, negative )
{
    Anime anime = Anime();
    anime.setEpisode( -1 );
    ASSERT_EQ( 1, anime.getCurrentEpisode() );
}
TEST( Anime_setEpisode, zero )
{
    Anime anime = Anime();
    anime.setEpisode( 0 );
    ASSERT_EQ( 1, anime.getCurrentEpisode() );
}
TEST( Anime_setEpisode, null )
{
    Anime anime = Anime();
    anime.setEpisode( NULL );
    ASSERT_EQ( 1, anime.getCurrentEpisode() );
}

/**************************/
/* Anime::setTotalEpisodes */
/**************************/
TEST( Anime_setTotalEpisodes, valid1 )
{
    Anime anime = Anime();
    anime.setTotalEpisodes( 5 );
    ASSERT_EQ( 5, anime.getTotalEpisodes() );
}
TEST( Anime_setTotalEpisodes, negative )
{
    Anime anime = Anime();
    anime.setTotalEpisodes( -5 );
    ASSERT_EQ( MAX_NUMBER_EPISODES, anime.getTotalEpisodes() );
}
TEST( Anime_setTotalEpisodes, zero )
{
    Anime anime = Anime();
    anime.setTotalEpisodes( 0 );
    ASSERT_EQ( MAX_NUMBER_EPISODES, anime.getTotalEpisodes() );
}
TEST( Anime_setTotalEpisodes, null )
{
    Anime anime = Anime();
    anime.setTotalEpisodes( NULL );
    ASSERT_EQ( MAX_NUMBER_EPISODES, anime.getTotalEpisodes() );
}

/*****************/
/* Anime::setUrl */
/*****************/
TEST( Anime_setUrl, http )
{
    Anime anime = Anime();
    anime.setUrl( "http://www.google.de" );
    ASSERT_EQ( "http://www.google.de", anime.getUrl() );
}
TEST( Anime_setUrl, https )
{
    Anime anime = Anime();
    anime.setUrl( "https://www.google.de" );
    ASSERT_EQ( "https://www.google.de", anime.getUrl() );
}
TEST( Anime_setUrl, ftp )
{
    Anime anime = Anime();
    anime.setUrl( "ftp://www.google.de" );
    ASSERT_EQ( "", anime.getUrl() );
}
TEST( Anime_setUrl, randomChars )
{
    Anime anime = Anime();
    anime.setUrl( "fhsdfhsdfhsdfh" );
    ASSERT_EQ( "", anime.getUrl() );
}
TEST( Anime_setUrl, number )
{
    Anime anime = Anime();
    anime.setUrl( "276243572" );
    ASSERT_EQ( "", anime.getUrl() );
}
TEST( Anime_setUrl, specialChars )
{
    Anime anime = Anime();
    anime.setUrl( "#+-.," );
    ASSERT_EQ( "", anime.getUrl() );
}
TEST( Anime_setUrl, httpNeedsTrim1 )
{
    Anime anime = Anime();
    anime.setUrl( "http://www.google.de   " );
    ASSERT_EQ( "http://www.google.de", anime.getUrl() );
}
TEST( Anime_setUrl, httpNeedsTrim2 )
{
    Anime anime = Anime();
    anime.setUrl( "   http://www.google.de" );
    ASSERT_EQ( "http://www.google.de", anime.getUrl() );
}
TEST( Anime_setUrl, httpNeedsTrim3 )
{
    Anime anime = Anime();
    anime.setUrl( "   http://www.google.de   " );
    ASSERT_EQ( "http://www.google.de", anime.getUrl() );
}
// functionality to detect not implemented and not needed
//TEST( Anime_setUrl, specialCharsWithHttpPrefix )
//{
//    Anime anime = Anime( );
//    anime.setUrl( "http://#+-.," );
//    ASSERT_EQ( "", anime.getUrl( ) );
//}

/**********************/
/* Anime::validateUrl */
/**********************/
TEST( Anime_validateUrl, http )
{
    ASSERT_EQ( true, Anime::validateURL( "http://www.google.de" ) );
}
TEST( Anime_validateUrl, https )
{
    ASSERT_EQ( true, Anime::validateURL( "https://www.google.de" ) );
}
TEST( Anime_validateUrl, randomChars )
{
    ASSERT_EQ( false, Anime::validateURL( "gfbwrthjertj" ) );
}

/****************************/
/* Anime::validateAnimeMame */
/****************************/
TEST( Anime_validateAnimeName, validName1 )
{
    std::string expected = "Clannad";
    std::string actual = "Clannad";
    Anime::validateAnimeName( actual );
    ASSERT_EQ( expected, actual );
}
TEST( Anime_validateAnimeName, invalidName1 )
{
    std::string expected = "Asdf[";
    std::string actual = "asdf(";
    Anime::validateAnimeName( actual );
    ASSERT_EQ( expected, actual );
}
TEST( Anime_validateAnimeName, invalidName2 )
{
    std::string expected = "Asdf]";
    std::string actual = "asdf)";
    Anime::validateAnimeName( actual );
    ASSERT_EQ( expected, actual );
}
TEST( Anime_validateAnimeName, invalidName3 )
{
    std::string expected = "Asdf[]";
    std::string actual = "asdf()";
    Anime::validateAnimeName( actual );
    ASSERT_EQ( expected, actual );
}
TEST( Anime_validateAnimeName, invalidName4 )
{
    std::string expected = "[asdf]asdf";
    std::string actual = "(asdf)asdf";
    Anime::validateAnimeName( actual );
    ASSERT_EQ( expected, actual );
}

/*********************/
/* Anime::incEpisode */
/*********************/
TEST( Anime_incEpisode, increase )
{
    Anime anime = Anime();
    anime.setEpisode( 5 );
    anime.incEpisode();
    ASSERT_EQ( 6, anime.getCurrentEpisode() );
}
TEST( Anime_incEpisode, increaseAtLimit )
{
    Anime anime = Anime();
    anime.setEpisode( MAX_NUMBER_EPISODES );
    anime.incEpisode();
    ASSERT_EQ( MAX_NUMBER_EPISODES, anime.getCurrentEpisode() );
}

/*********************/
/* Anime::decEpisode */
/*********************/
TEST( Anime_decEpisode, decrease )
{
    Anime anime = Anime();
    anime.setEpisode( 5 );
    anime.decEpisode();
    ASSERT_EQ( 4, anime.getCurrentEpisode() );
}
TEST( Anime_decEpisode, decreaseAtLimit )
{
    Anime anime = Anime();
    anime.setEpisode( 1 );
    anime.decEpisode();
    ASSERT_EQ( 1, anime.getCurrentEpisode() );
}

/********************/
/* Anime::operator< */
/********************/
TEST( Anime_operatorLess, isLess0 )
{
    Anime less = Anime( "attack On Titan" );
    Anime greater = Anime( "clannad" );
    ASSERT_TRUE( less < greater );
}
TEST( Anime_operatorLess, isLess1 )
{
    Anime less = Anime( "Attack On Titan" );
    Anime greater = Anime( "Clannad" );
    ASSERT_TRUE( less < greater );
}
TEST( Anime_operatorLess, isLess2 )
{
    Anime less = Anime( "clannad" );
    Anime greater = Anime( "Yuri" );
    ASSERT_TRUE( less < greater );
}
TEST( Anime_operatorLess, isLess3 )
{
    Anime less = Anime( "Clannad" );
    Anime greater = Anime( "yuri" );
    ASSERT_TRUE( less < greater );
}
TEST( Anime_operatorLess, isNotLess1 )
{
    Anime less = Anime( "Attack On Titan" );
    Anime greater = Anime( "Clannad" );
    ASSERT_FALSE( greater < less );
}

/*******************/
/* Anime::toString */
/*******************/
TEST( Anime_toString, titelOnly )
{
    Anime anime = Anime( "Hayamata" );
    ASSERT_EQ( anime.toString(), "Hayamata (Episode 1 / ??)" );
}
TEST( Anime_toString, titelAndCurrentEpisode )
{
    Anime anime = Anime( "Hayamata", 5 );
    ASSERT_EQ( anime.toString(), "Hayamata (Episode 5 / ??)" );
}
TEST( Anime_toString, onlyUrlMissing )
{
    Anime anime = Anime( "Clannad", 1, 12 );
    ASSERT_EQ( anime.toString(), "Clannad (Episode 1 / 12)" );
}
TEST( Anime_toString, fullConstructorSetup )
{
    Anime anime = Anime( "Yuri", 1, 12, "http://www.google.de" );
    ASSERT_EQ( anime.toString(), "Yuri (Episode 1 / 12)" );
}

/****************************/
/* StringUtils::isLowercase */
/****************************/
TEST( StringUtils_isLowercase, isLowercase1 )
{
    ASSERT_EQ( true, StringUtils::isLowercase( "clannad" ) );
}
TEST( StringUtils_isLowercase, isLowercase2 )
{
    ASSERT_EQ( true, StringUtils::isLowercase( "alf" ) );
}
TEST( StringUtils_isLowercase, isLowercase3 )
{
    ASSERT_EQ( true, StringUtils::isLowercase( "zalf" ) );
}
TEST( StringUtils_isLowercase, plus1error )
{
    ASSERT_EQ( false, StringUtils::isLowercase( "{lf" ) );
}
TEST( StringUtils_isLowercase, minus1error )
{
    ASSERT_EQ( false, StringUtils::isLowercase( "`lf" ) );
}
TEST( StringUtils_isLowercase, isUppercase1 )
{
    ASSERT_EQ( false, StringUtils::isLowercase( "Alf" ) );
}
TEST( StringUtils_isLowercase, isUppercase2 )
{
    ASSERT_EQ( false, StringUtils::isLowercase( "Zlf" ) );
}
TEST( StringUtils_isLowercase, empty )
{
    ASSERT_EQ( false, StringUtils::isLowercase( "" ) );
}

/****************************/
/* StringUtils::isUppercase */
/****************************/
TEST( StringUtils_isUppercase, isUppercase1 )
{
    ASSERT_EQ( true, StringUtils::isUppercase( "Alf" ) );
}
TEST( StringUtils_isUppercase, isUppercase2 )
{
    ASSERT_EQ( true, StringUtils::isUppercase( "Zlf" ) );
}
TEST( StringUtils_isUppercase, isUppercase3 )
{
    ASSERT_EQ( true, StringUtils::isUppercase( "Ulf" ) );
}
TEST( StringUtils_isUppercase, FirstNotUppercase )
{
    ASSERT_EQ( false, StringUtils::isUppercase( "aIUHBFIAB" ) );
}
TEST( StringUtils_isUppercase, empty )
{
    ASSERT_EQ( false, StringUtils::isUppercase( "" ) );
}
TEST( StringUtils_isUppercase, plus1error )
{
    ASSERT_EQ( false, StringUtils::isUppercase( "[asfasf" ) );
}
TEST( StringUtils_isUppercase, minus1error )
{
    ASSERT_EQ( false, StringUtils::isUppercase( "@asfasf" ) );
}
TEST( StringUtils_isUppercase, numbers1 )
{
    ASSERT_EQ( false, StringUtils::isUppercase( "130857" ) );
}
TEST( StringUtils_isUppercase, specialChars1 )
{
    ASSERT_EQ( false, StringUtils::isUppercase( "#+-." ) );
}

/************************/
/* StringUtils::toLower */
/************************/
TEST( StringUtils_toLower, isLowercase1 )
{
    std::string expected = "clannad";
    std::string actual = "clannad";
    StringUtils::toLower( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toLower, isNotLowercase1 )
{
    std::string expected = "clannad";
    std::string actual = "Clannad";
    StringUtils::toLower( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toLower, numbers1 )
{
    std::string expected = "1239571";
    std::string actual = "1239571";
    StringUtils::toLower( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toLower, specialChars1 )
{
    std::string expected = "#+*-.";
    std::string actual = "#+*-.";
    StringUtils::toLower( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toLower, empty )
{
    std::string expected = "";
    std::string actual = "";
    StringUtils::toLower( actual );
    ASSERT_EQ( expected, actual );
}

/************************/
/* StringUtils::toUpper */
/************************/
TEST( StringUtils_toUpper, isUppercase1 )
{
    std::string expected = "Clannad";
    std::string actual = "Clannad";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, isUppercase2 )
{
    std::string expected = "Alf";
    std::string actual = "Alf";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, isUppercase3 )
{
    std::string expected = "Zalf";
    std::string actual = "Zalf";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, isLowercase1 )
{
    std::string expected = "Alf";
    std::string actual = "alf";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, isLowercase2 )
{
    std::string expected = "Zlf";
    std::string actual = "zlf";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, numbers )
{
    std::string expected = "245623572";
    std::string actual = "245623572";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, specialChars )
{
    std::string expected = "#+-.";
    std::string actual = "#+-.";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}
TEST( StringUtils_toUpper, empty )
{
    std::string expected = "";
    std::string actual = "";
    StringUtils::toUpper( actual );
    ASSERT_EQ( expected, actual );
}

/************************/
/* Animelist::Animelist */
/************************/
TEST( Animelist_Constructor, noArguments )
{
    Animelist al;
    ASSERT_TRUE( al.getAnimeList().empty() );
}
TEST( Animelist_Constructor, argumentIsList )
{
    std::list<Anime*> list;
    list.push_back( new Anime( "Clannad", 1, 26, "https://www.google.de" ) );
    Animelist al(list); // deletes list
    ASSERT_EQ( al.getAnimeList().size(), 1 );
}
TEST( Animelist_Constructor, argumentListEmpty )
{
    std::list<Anime*> list;
    Animelist al( list ); // deletes list
    ASSERT_EQ( al.getAnimeList().size(), 0 );
}

/************************/
/* Animelist::operator= */
/************************/
TEST( Animelist_operatorAssignment, assignWithEquals )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Log Horizon" ) );
    Animelist alCopy;
    alCopy = al;
    ASSERT_EQ( alCopy.getAnimeList().size(), 2 );
}

/***********************/
/* Animelist::isInList */
/***********************/
TEST( Animelist_isInList, inList )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Log Horizon" ) );
    ASSERT_TRUE( al.isInList( Anime( "Clannad" ) ) );
}
TEST( Animelist_isInList, notInList )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Log Horizon" ) );
    ASSERT_FALSE( al.isInList( Anime( "Werwolf" ) ) );
}

/***********************/
/* Animelist::addAnime */
/***********************/
TEST( Animelist_addAnime, valid )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_EQ( al.getAnimeList().size(), 1 );
    ASSERT_EQ( al.getAnimeByName( "Clannad" )->getName(), "Clannad" );
}

/*******************/
/* Animelist::sort */
/*******************/
TEST( Animelist_sort, sort )
{
    Animelist al;
    al.addAnime( new Anime( "Prison School" ) );
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Acchi Kocchi" ) );
    al.addAnime( new Anime( "Beelzebub" ) );
    al.sort();

    std::list<Anime*> sortedList;
    sortedList.push_back( new Anime( "Acchi Kocchi" ) );
    sortedList.push_back( new Anime( "Beelzebub" ) );
    sortedList.push_back( new Anime( "Clannad" ) );
    sortedList.push_back( new Anime( "Prison School" ) );
    std::list<Anime*>::const_iterator it = sortedList.cbegin();

    for ( size_t i = 0; i < al.size(); ++i, ++it )
    {
        ASSERT_STREQ( al[i]->getName().c_str(), ( *it )->getName().c_str() );
    }
}

/*********************************************************/
/* Animelist::CompareAnimeObjectsBehindPointersAscending */
/*********************************************************/
TEST( Animelist_CompareAnimeObjectsBehindPointersAscending, compare )
{
    Anime prisonSchool( "Prison School" );
    Anime clannad( "Clannad" );
    Anime acchiKocchi( "Acchi Kocchi" );
    Anime beelzebub( "Beelzebub" );

    ASSERT_TRUE( Animelist::CompareAnimeObjectsBehindPointersAscending(
        &clannad,
        &prisonSchool ) ); // clannad < prison school
    ASSERT_TRUE( Animelist::CompareAnimeObjectsBehindPointersAscending(
        &acchiKocchi,
        &beelzebub ) ); // acchi kocchi < beelzebub
    ASSERT_FALSE( Animelist::CompareAnimeObjectsBehindPointersAscending(
        &prisonSchool,
        &beelzebub ) ); // !( prison school < beelzebub )
}

/*********************************************/
/* Animelist::getAnimeNameFromToStringPhrase */
/*********************************************/
TEST( Animelist_getAnimeNameFromToStringPhrase, valid )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_STREQ( Animelist::getAnimeNameFromToStringPhrase( "Clannad (Episode 1 of 26)" ).c_str(), "Clannad" );
}
TEST( Animelist_getAnimeNameFromToStringPhrase, inValid )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_THROW( Animelist::getAnimeNameFromToStringPhrase( "Clannad 1 of 26" ).c_str(), std::invalid_argument );
}

/*****************************/
/* Animelist::getAnimeByName */
/*****************************/
TEST( Animelist_getAnimeByName, valid )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_STREQ( al.getAnimeByName( "Clannad" )->getName().c_str(), al[0]->getName().c_str() );
}
TEST( Animelist_getAnimeByName, inValid )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_EQ( al.getAnimeByName( "asdf" ), nullptr );
}

/********************************/
/* Animelist::deleteAnimeByName */
/********************************/
TEST( Animelist_deleteAnimeByName, deleteOne )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    al.deleteAnimeByName( "Clannad" );
    ASSERT_EQ( al.getAnimeList().size(), 0 );
}
TEST( Animelist_deleteAnimeByName, deleteThree )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Konosuba" ) );
    al.addAnime( new Anime( "Charlotte" ) );
    al.deleteAnimeByName( "Clannad" );
    al.deleteAnimeByName( "Konosuba" );
    al.deleteAnimeByName( "Charlotte" );
    ASSERT_EQ( al.getAnimeList().size(), 0 );
}
TEST( Animelist_deleteAnimeByName, wrongName )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    al.deleteAnimeByName( "asdf" );
    ASSERT_EQ( al.getAnimeList().size(), 1 );
}
TEST( Animelist_deleteAnimeByName, twoTimes )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_TRUE( al.deleteAnimeByName( "Clannad" ) );
    ASSERT_FALSE( al.deleteAnimeByName( "Clannad" ) );
    ASSERT_EQ( al.getAnimeList().size(), 0 );
}

/**********************/
/* Animelist::isEmpty */
/**********************/
TEST( Animelist_isEmpty, empty )
{
    Animelist al;
    ASSERT_TRUE( al.isEmpty() );
}
TEST( Animelist_isEmpty, notEmpty )
{
    Animelist al;
    al.addAnime( new Anime( "Clannad" ) );
    ASSERT_FALSE( al.isEmpty() );
}

/************************************************/
/* Animelist::popOutByNameWithoutDeletingMemory */
/************************************************/
TEST( Animelist_popOutByNameWithoutDeletingMemory, existingObject )
{
    Animelist al;
    Anime* clannad = new Anime( "Clannad" );
    al.addAnime( clannad );
    al.popOutByNameWithoutDeletingMemory( "Clannad" );
    ASSERT_NE( clannad, nullptr );
    ASSERT_STREQ( clannad->getName().c_str(), "Clannad" ); // clannad still accessible
    ASSERT_TRUE( al.isEmpty() ); // but list is empty
}
TEST( Animelist_popOutByNameWithoutDeletingMemory, nonExistingObject )
{
    Animelist al;
    Anime* clannad = new Anime( "Clannad" );
    al.addAnime( clannad );
    al.popOutByNameWithoutDeletingMemory( "asdf" );
    ASSERT_EQ( al.size(), 1 ); // nothing popped out
}

/*******************/
/* Animelist::size */
/*******************/
TEST( Animelist_size, 4Elements )
{
    Animelist al;
    al.addAnime( new Anime( "Prison School" ) );
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Acchi Kocchi" ) );
    al.addAnime( new Anime( "Beelzebub" ) );
    ASSERT_EQ( al.size(), 4 );
}
TEST( Animelist_size, 1Element )
{
    Animelist al;
    al.addAnime( new Anime( "Prison School" ) );
    ASSERT_EQ( al.size(), 1 );
}
TEST( Animelist_size, 0Element )
{
    Animelist al;
    ASSERT_EQ( al.size(), 0 );
}

/*************************/
/* Animelist::operator[] */
/*************************/
TEST( Animelist_operatorIndex, validIndex )
{
    Animelist al;
    al.addAnime( new Anime( "Prison School" ) );
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Acchi Kocchi" ) );
    al.addAnime( new Anime( "Beelzebub" ) );
    ASSERT_EQ( al[0]->getName(), "Prison School" );
    ASSERT_EQ( al[1]->getName(), "Clannad" );
    ASSERT_EQ( al[2]->getName(), "Acchi Kocchi" );
    ASSERT_EQ( al[3]->getName(), "Beelzebub" );
}
TEST( Animelist_operatorIndex, invalidIndex )
{
    Animelist al;
    al.addAnime( new Anime( "Prison School" ) );
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Acchi Kocchi" ) );
    al.addAnime( new Anime( "Beelzebub" ) );
    ASSERT_THROW( al[4], std::out_of_range );
    ASSERT_THROW( al[-1], std::out_of_range );
}

/********************/
/* Animelist::clear */
/********************/
TEST( Animelist_clear, clear )
{
    Animelist al;
    al.addAnime( new Anime( "Prison School" ) );
    al.addAnime( new Anime( "Clannad" ) );
    al.addAnime( new Anime( "Acchi Kocchi" ) );
    al.addAnime( new Anime( "Beelzebub" ) );
    al.clear();
    ASSERT_EQ( al.size(), 0 );
}


int main( int argc, char* argv[] )
{
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
