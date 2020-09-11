#ifndef GLOBALS_H
#define GLOBALS_H

const char PROGRAM_NAME[] = "Anwalic";
const char PROGRAM_VERSION[] = "1.4 DevBuild 2";
const char ERROR_FILENAME[] = "Anwalic_error_description.ane";
const char DEFAULT_BACKGROUND_IMAGE_PATH[] = "./backgrounds/anime_background_1.jpg";
const char DEFAULT_ANIME_LIST_PATH[] = "mylist.anl";
const char DEFAULT_ANIME_LIST_COMPLETED_PATH[] = "mylist_completed.anl";

const unsigned int MAX_NUMBER_EPISODES = 4096; // no anime will ever have 4k episodes. not risky to increase value
const unsigned int MAX_ANIME_NAME_LENGTH = 200;

#endif // GLOBALS_H
