/* 
 * File:   main.cpp
 * Author: master312
 *
 * Created on August 13, 2015, 7:58 PM
 * TEst
 */
#include "game/cGame.h"

#ifdef OS_WINDOWS
#undef main
#endif

int main(int argc, char** argv) {
        // doxygen comment example
        //////////////////////////////////////////////////////////////////////////////////////////
        /// static void GetRbgBonus(Player *pl, uint32 *honorWin, uint32 *honorLost, uint32 *arenaPoints)
        /// \note   Calculates honor bonus for playing RBG
        ///         If nullptr is passed for any argument except *arenaLost, it will cause crush
        ///
        /// \param  Player *pl  -  Pointer to player object
        /// \param  uint32 *honorWin  -  Bonus honor for winning
        /// \param  uint32 *honorLost -  Bonus honor for losing
        /// \param  uint32 *arenaWin -  Arena points rewarded for winning
        /// \param  uint32 *arenaLost -  Arena points rewarded losing
        ///
        /// \return none
        ///
        //////////////////////////////////////////////////////////////////////////////////////////
    
    cGame *g = new cGame();
    g->Start();
    delete g;

    return 0;
}

