#include "Commands.hpp"

bool  TOPIC::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]))
    {
        if (cmd.getTokens().size() > 2 && cli->getNickname() == serv.getChannel(cmd.getTokens()[1])->getOperator())
        {
            string topic = cmd.getTokens()[2].substr(1);
            for (size_t i = 3; i < cmd.getTokens().size(); i++)
                topic += " " + cmd.getTokens()[i];
            serv.getChannel(cmd.getTokens()[1])->setTopic(topic);
            serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " TOPIC " + cmd.getTokens()[1] + " :" + topic + "\r\n");
        }
        else
            cli->sendReply("332 " + cli->getNickname() + " " + cmd.getTokens()[1] + " :" + serv.getChannel(cmd.getTokens()[1])->getTopic() + "\r\n");
    }
    return true;
}