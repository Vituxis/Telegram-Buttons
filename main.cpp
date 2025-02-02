#include <tgbot/tgbot.h>
#include <iostream>

int main() {
    std::string API_KEY = <your api here>;
    TgBot::Bot bot(API_KEY);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        std::string nome = message->from->firstName;
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup());

        std::vector<TgBot::InlineKeyboardButton::Ptr> row;
        std::vector<TgBot::InlineKeyboardButton::Ptr> row2;
        std::vector<TgBot::InlineKeyboardButton::Ptr> row3;

        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton());
        TgBot::InlineKeyboardButton::Ptr button2(new TgBot::InlineKeyboardButton());
        TgBot::InlineKeyboardButton::Ptr button3(new TgBot::InlineKeyboardButton());

        button->text = "Clique no botao 1";
        button->callbackData = "botao1";
        button2->text = "Clique no botao 2";
        button2->callbackData = "botao2";
        button3->text = "Clique no botao 3";
        button3->callbackData = "botao3";

        row.push_back(button);
        row2.push_back(button2);
        row3.push_back(button3);

        keyboard->inlineKeyboard.push_back(row);
        keyboard->inlineKeyboard.push_back(row2);
        keyboard->inlineKeyboard.push_back(row3);

        bot.getApi().sendMessage(
            message->chat->id, 
            nome + ", clique em um dos botoes abaixo para ver a mensagem!",
            nullptr,     
            nullptr,        
            keyboard
        );
    });

    bot.getEvents().onCallbackQuery([&bot](TgBot::CallbackQuery::Ptr query) {
        if (query->data == "botao1") { 
            bot.getApi().sendMessage(query->message->chat->id, "Você clicou no botão 1");
        } else if (query->data == "botao2") {
            bot.getApi().sendMessage(query->message->chat->id, "Você clicou no botao 2");
        } else {
            bot.getApi().sendMessage(query->message->chat->id, "Você clicou no botão 3");
        }
        bot.getApi().answerCallbackQuery(query->id);
    });

    try {
        std::cout << "Bot rodando..." << std::endl;
        bot.getApi().deleteWebhook();
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}