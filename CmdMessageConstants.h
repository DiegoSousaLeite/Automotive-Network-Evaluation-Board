#ifndef CMDMESSAGECONSTANTS_H
#define CMDMESSAGECONSTANTS_H

#include <QString>

class CmdMessageConstants {
public:
    // Communication test
    static constexpr char CMD_ERROR_TEST_EXECUTION[] = "Erro na execução do teste";
    static constexpr char CMD_SUCCESS_TEST_EXECUTION[] = "Sucesso execução do teste";

    static constexpr char MSG_INVALID_TEST[] = "Teste inválido";
    static constexpr char MSG_UNAVAILABLE_SERIAL_PORT[] = "Portas seriais não disponíveis";
    static constexpr char MSG_SUCCESS_OPEN_SERIAL_PORT[] = "Porta serial aberta com sucesso";
    static constexpr char MSG_SUCCESS_CLOSE_SERIAL_PORT[] = "Porta serial fechada com sucesso";
    static constexpr char MSG_SEND_AT_COMMAND[] = "Enviando comando AT";
    static constexpr char MSG_READING_RECEIVED_MESSAGE[] = "Lendo a mensagem recebida";
    static constexpr char MSG_WAITING_TEST_RESULT[] = "Aguardando o resultado do teste...";
    static constexpr char MSG_WAITING_DIGITAL_TEST[] = "Pressione os botões (5s)";
    static constexpr char MSG_WAITING_ANALOG_TEST[] = "Gire os potenciômetros (20s)";
    static constexpr char MSG_INVALID_SERIAL_PORT[] = "Porta serial inválida";
    static constexpr char MSG_ERROR_TO_RUN_TEST[] = "Erro na execução do teste";
    static constexpr char MSG_ERROR_TO_OPEN_PORT[] = "Erro para abrir a porta serial";
    static constexpr char MSG_SUCCESS_START_TEST[] = "Teste iniciado com sucesso";
    static constexpr char MSG_SUCCESS_EXECUTE_TEST[] = "Sucesso na execução do teste";
    static constexpr char MSG_PROGRAMMER_MODE[] = "Programador em modo";
    static constexpr char MSG_START_FIRMWARE_UPDATE[] = "Iniciando a atualização de firmware...";
    static constexpr char MSG_NOT_FOUND_PROGRAMMER[] = "Programador de firmware não encontrado";
    static constexpr char MSG_TRY_LOAD_PROGRAMMER[] = "Tentando carregar o programador...";
    static constexpr char MSG_SUCCESS_LOAD_PROGRAMMER[] = "Sucesso no carregamento do programador";

    static constexpr char MSG_BOARD_ON_SERIAL_PORT[] = "Porta serial atribuída a";
    static constexpr char MSG_TRY_CONNECTION_AGAIN[] = "Tentando uma nova conexão";

    static constexpr char MSG_LOAD_BOARD_INFO[] = "Identificando portas seriais";

    static constexpr char MSG_ERR_START_TEST[] = "Erro para iniciar o teste!";

    static constexpr char MSG_SEPARATOR[] = ": ";

    static constexpr char CMD_HDR_COMMUNICATION[] = "COMMT:";
    static constexpr char CMD_HDR_DIGITAL_INPUT[] = "DINPT:";
    static constexpr char CMD_HDR_ANALOG_INPUT[] = "AINPT:";
    static constexpr char CMD_HDR_ANALOG_OUTPUT[] = "ANOUT:";
    static constexpr char CMD_HDR_LOOPBACK_CAN[] = "COMMT:";
    static constexpr char CMD_HDR_CAN_INIT[] = "CANIT:";
    static constexpr char CMD_HDR_CAN1_NETWORK[] = "CAN1T:";
    static constexpr char CMD_HDR_CAN2_NETWORK[] = "CAN2T:";
    static constexpr char CMD_HDR_LIN_NETWORK[] = "LINNT:";
    static constexpr char CMD_HDR_FIRM_UPLOAD[] = "FUPLD:";
    static constexpr char CMD_HDR_MCU_INTERFACE[] = "MCUIT:";

    static constexpr char CMD_MSG_COMMUNICATION[] = "Teste de comunicação";
    static constexpr char CMD_MSG_DIGITAL_INPUT[] = "Teste das entradas digitais";
    static constexpr char CMD_MSG_ANALOG_INPUT[] = "Teste das entradas analógicas";
    static constexpr char CMD_MSG_ANALOG_OUTPUT[] = "Teste das saídas analógicas";
    static constexpr char CMD_MSG_CAN_INIT[] = "Teste de inicialização CAN";
    static constexpr char CMD_MSG_LOOPBACK_CAN[] = "Teste de loopback CAN";
    static constexpr char CMD_MSG_CAN1_NETWORK[] = "Teste da rede CAN BUS1";
    static constexpr char CMD_MSG_CAN2_NETWORK[] = "Teste da rede CAN BUS2";
    static constexpr char CMD_MSG_LIN_NETWORK[] = "Teste da rede LIN";
    static constexpr char CMD_MSG_FIRM_UPDATE[] = "Atualização de firmware";
    static constexpr char CMD_MSG_MCU_INTERFACE[] = "Teste de interface da MCU";
};

#endif // CMDMESSAGECONSTANTS_H
