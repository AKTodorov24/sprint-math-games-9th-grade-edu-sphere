#include "config/libraries.h"
#include "visuals/centering.h"
#include "visuals/title.h"
#include "domain/users/auth.h"
int main() {
    enableCenteredOutput();
    displayTitle();
    std::string currentUser;
    authMenu(currentUser);
    return 0;
}