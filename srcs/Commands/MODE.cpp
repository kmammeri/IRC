#include "Commands.hpp"

bool  MODE::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]))
    {
        // cout << "number of users = " << serv.getChannel(cmd.getTokens()[1])->getUsers().size() << endl;
        if (cmd.getTokens().size() == 2)
        {
            switch(serv.getChannel(cmd.getTokens()[1])->getMode())
            {
                case PUBLIC:
                {
                    cli->sendReply(":" + string(SERVER_NAME) + " 324 " + cli->getNickname() + " " + cmd.getTokens()[1] + " +t\r\n");
                    break;
                }
                case PRIVATE:
                {
                     cli->sendReply(":" + string(SERVER_NAME) + " 324 " + cli->getNickname() + " " + cmd.getTokens()[1] + " +p\r\n");
                    break;
                }
                case INVITE_ONLY:
                {
                    cli->sendReply(":" + string(SERVER_NAME) + " 324 " + cli->getNickname() + " " + cmd.getTokens()[1] + " +i\r\n");
                    break;
                }
                case PRIVATE_WITH_INVITE:
                {
                    cli->sendReply(":" + string(SERVER_NAME) + " 324 " + cli->getNickname() + " " + cmd.getTokens()[1] + " +p +i\r\n");
                    break;
                }
                default:
                    break;
        }
    }
        if (cmd.getTokens().size() > 2 && cli->getNickname() == serv.getChannel(cmd.getTokens()[1])->getOperator())
        {
            if (cmd.getTokens()[2] == "+o")
            {
                if (cmd.getTokens().size() == 2)
                {
                    cli->sendReply(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " +o " + cli->getNickname() + "\r\n");
                    return true;
                }
                Client    *target = serv.getClientByNick(cmd.getTokens()[3]);
                // cout << "test target = " << target->getNickname() << endl;
                if (target)
                {
                    serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " +o " + target->getNickname() + "\r\n");
                    serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " -o " + serv.getChannel(cmd.getTokens()[1])->getOperator() + "\r\n");
                    serv.getChannel(cmd.getTokens()[1])->setOperator(target->getNickname());
                }
                else
                {
                    cli->sendReply(":" + string(SERVER_NAME) + " 401 " + cli->getNickname() + " " + cmd.getTokens()[3] + " :No such nick/channel\r\n");
                }
            }
            else if (cmd.getTokens()[2] == "-o")
            {
                Client *target = serv.getClientByNick(cmd.getTokens()[3]);
                if (target)
                {
                    serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " -o " + target->getNickname() + "\r\n");
                    serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " +o " + serv.getChannel(cmd.getTokens()[1])->getFirstUser() + "\r\n");
                    serv.getChannel(cmd.getTokens()[1])->setOperator(serv.getChannel(cmd.getTokens()[1])->getFirstUser());
                }
                else
                {
                    cli->sendReply(":" + string(SERVER_NAME) + " 401 " + cli->getNickname() + " " + cmd.getTokens()[3] + " :No such nick/channel\r\n");
                }
            }
        }
        else if (cmd.getTokens().size() > 2 && cli->getNickname() != serv.getChannel(cmd.getTokens()[1])->getOperator())
        {
            cli->sendReply(":" + string(SERVER_NAME) + " 482 " + cli->getNickname() + " " + cmd.getTokens()[1] + " :You're not channel operator\r\n");
        }
    }
    return true;
}