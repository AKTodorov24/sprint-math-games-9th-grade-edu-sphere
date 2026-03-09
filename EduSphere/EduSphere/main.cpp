#include "config/libraries.h"
#include "visuals/centering.h"
#include "visuals/title.h"
#include "visuals/mainMenu.h"
#include "domain/users/auth.h"

int main() {
    enableCenteredOutput();
    displayTitle();

    std::string currentUser;
    int currentUserID = 0;
    authMenu(currentUser, currentUserID);
    runApp(currentUser, currentUserID);

    return 0;
}
