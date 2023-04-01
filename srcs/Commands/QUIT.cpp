#include "Commands.hpp"

bool  QUIT::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    for(size_t i = 0; i < serv.getChannels().size(); i++)
    {
        vector<string> list = serv.getVectChannels();
        for (long unsigned int j = 0; j < list.size(); j++)
        {
            if (serv.getChannel(list[j])->getInviteListe().find(cli->getNickname()) != serv.getChannel(list[j])->getInviteListe().end())
            {
                serv.getChannel(list[j])->removeInvite(cli);
            }
            if (serv.getChannel(list[j])->getUsers().find(cli->getNickname()) != serv.getChannel(list[j])->getUsers().end())
            {
                serv.getChannel(list[j])->removeUser(cli);
                if (serv.getChannel(list[j])->getUsers().size() != 0 && serv.getChannel(list[j])->getOperator() == cli->getNickname())
                {
                    serv.getChannel(list[j])->setOperator(serv.getChannel(list[j])->getFirstUser());
                    serv.getChannel(list[j])->sendToAll(":" + cli->getNickname() + " MODE " + list[j] + " +o " + serv.getChannel(list[j])->getFirstUser() + "\r\n");
                    serv.getChannel(list[j])->sendToAll(":" + cli->getNickname() + " MODE " + list[j] + " -o " + cli->getNickname() + "\r\n");
                }
                serv.getChannel(list[j])->sendToAll(":" + cli->getNickname() + " QUIT :" + cmd.getTokens()[1] + "\r\n");
            }
        }
    }
    return true;
}