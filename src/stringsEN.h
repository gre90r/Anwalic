#ifndef STRINGSEN_H
#define STRINGSEN_H

#include "globals.h"
#include <string>

const char STR_INVALID_URL[] = "URL is invalid! It needs a \"http://\" or \"https://\" prefix. It is also allowed to "
    "leave it blank. You can add it later by using the Edit feature.";
const char STR_INVALID_TOTAL_EPISODES[] = "Total number of Episodes is invalid!";
const char STR_INVALID_NAME[] = "Name is invalid!";
const char STR_INVALID_CURRENT_EPISODE[] = "Current Episode is invalid!";
const char STR_INTERNAL_ERROR_STANDARD_MESSAGE[] = "internal error! This is a programming mistake. "
    "Please report to me. An error file has been created for that reason in the program directory. "
    "Contact information can be found under Help -> About.";
const char STR_ANIME_ALREADY_IN_LIST[] = "Anime is already in your list.";
const char STR_YOU_CHOSE[] = "You chose";
const char STR_WHAT_DO_YOU_WANT_TO_DO[] = "What do you want to do?";
const char STR_NOTHING[] = "Nothing";
const char STR_DELETE[] = "Delete";
const char STR_EDIT[] = "Edit";
const char STR_DO_YOU_REALLY_WANT_TO_DELETE[] = "Do you really want to delete";
const char STR_FROM_THE_LIST_FOREVER[] = "from the list forever?";
const char STR_YOU_DID_NOT_SPECIFY_A_URL[] = "You didn't specify a URL. But you can add one by using the Edit feature. "
    "Just double-click on the anime in your list.";
const char STR_FAILED_TO_OPEN_URL_YOU_TRIED_TO_ACCESS[] = "Failed to open URL! You tried to access";
const std::string STR_YOU_WONT_BE_ABLE_TO_SAVE_LOAD = std::string( "You won't be able to save/load properly! " ) +
    std::string( "Please check your save file name and location. It has to be located in the program directory. " ) +
    std::string( "That means it must be in the same folder like the executable. On Windows it's \"" ) +
    std::string( PROGRAM_NAME ) + std::string( ".exe\" on Linux \"" ) + std::string( PROGRAM_NAME ) +
    std::string( "\"." );
const char STR_YOUR_SAVE_FILE_IS_CORRUPTED[] = "Your save file is corrupted. Please delete the .anl file so "
    "that the program is able to start. In that case all your list entries will be gone. But at the moment "
    "there may be still fragments in the .anl file to save. Just open the file with a text editor.";
const char STR_EPISODE_PLUS_1[] = "Episode +1";
const char STR_MOVE_TO_COMPLETED_ANIMES[] = "Move to Completed Animes";
const char STR_COMPLETED_ANIMES[] = "Completed Animes";
const char STR_MY_ANIME_LIST[] = "My Anime List";
const char STR_MOVE_TO_MY_ANIMELIST[] = "Move to My Anime List";
const char STR_URL_CRUNCHYROLL_COM[] = "https://www.crunchyroll.com/";
const char STR_URL_WAKANIM_TV[] = "https://www.wakanim.tv/";
const char STR_YOUR_IMAGE_FILE_IS_UNREADABLE[] = "Your selected image file is unreadable. "
                                                 "Or the image file cannot be found. Please check the path to your image.";
const char STR_NO_BACKGROUND_CHOSEN[] = "No background chosen. Click on the button next to the text field "
                                        "to choose one or uncheck the Set Custom Background checkbox to go "
                                        "with the default background.";
const char STR_DO_YOU_WANT_TO_MOVE_THIS_ANIME_TO_COMPLETED_ANIME_LIST[] =
        "Do you want to move this Anime to the Completed Anime list? Every Anime "
        "you finished will be collected there.";
const char STR_CLEAR_FILTER[] = "Clear Filter";
const char STR_SHOW_STARTED_ANIMES_ONLY[] = "Show Started Animes Only";
const char STR_BACKUP_FAILED_COULD_NOT_COPY[] = "Backup failed! Could not copy mylist.anl and mylist_completed.anl";

#endif // STRINGSEN_H
