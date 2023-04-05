#include "Commands.hpp"

bool  LIST::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    (void)cmd;
    if (serv.getVectChannels().size() == 0)
        cli->sendReply("321 " + cli->getNickname() + " :No channels\r\n");
    else 
    {
        vector<string>  list = serv.getVectChannels();
        for (long unsigned int i = 0; i < list.size(); i++)
        {
            if (serv.getChannel(list[i])->getMode() != PRIVATE && serv.getChannel(list[i])->getMode() != PRIVATE_WITH_INVITE)
             cli->sendReply("322 " + cli->getNickname() + " " + list[i] + " :" + serv.getChannel(list[i])->getTopic() + "\r\n");
        }
        cli->sendReply("323 " + cli->getNickname() + " :End of LIST\r\n");
    }
    return true;
}