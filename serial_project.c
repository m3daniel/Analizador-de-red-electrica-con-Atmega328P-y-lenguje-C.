#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

#define SERIAL_PORT "COM9" //instrucción del puerto serie a usar

typedef struct{
    HANDLE handle;
    char buffer[255];
    DWORD bytes_read;
} SerialData;

void initSerialPort(SerialData* serialData){
    serialData->handle = CreateFile(SERIAL_PORT, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(serialData->handle == INVALID_HANDLE_VALUE){
        printf("Error to open serial port\n");
        exit(1);
    }
}

void configureSerialPort(SerialData* serialData){
    DCB dcbSerialParams;
    memset(&dcbSerialParams, 0, sizeof(dcbSerialParams));
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if(!GetCommState(serialData->handle, &dcbSerialParams)){
        printf("Error to obtain serial port state\n");
        CloseHandle(serialData->handle);
        exit(1);
    }


dcbSerialParams.BaudRate = CBR_9600; //velocidad de transmision de datos
dcbSerialParams.ByteSize = 8; //8 bits por byte
dcbSerialParams.StopBits = ONESTOPBIT; //un bit de parada
dcbSerialParams.Parity = NOPARITY; //sin paridad

if(!SetCommState(serialData->handle, &dcbSerialParams)){
    printf("Error to setting serial port state\n");
    CloseHandle(serialData->handle);
    exit(1);
}

COMMTIMEOUTS timeouts;
timeouts.ReadIntervalTimeout = 0;
timeouts.ReadTotalTimeoutMultiplier = 0;
timeouts.ReadTotalTimeoutConstant = 1000;
timeouts.WriteTotalTimeoutMultiplier = 0;
timeouts.WriteTotalTimeoutConstant = 0;

if(!SetCommTimeouts(serialData->handle, &timeouts)){
    printf("Error to configure serial port timeouts\n");
    CloseHandle(serialData->handle);
    exit(1);
}

}

void readData(SerialData* serialData){
	//from
	FILE *fp;
    fp = fopen("datos_serial.txt", "w"); // Abre el archivo de texto para escritura

    if(fp == NULL){
        printf("Error al abrir el archivo de texto\n");
        CloseHandle(serialData->handle);
		
        exit(1);
    }
	//till
	
    while(1){
    if(ReadFile(serialData->handle, serialData->buffer, sizeof(serialData->buffer)-1, &serialData->bytes_read, NULL)){
        serialData->buffer[serialData->bytes_read] = '\0';
        printf("Datos recibidos: %s\n", serialData->buffer);
		
		//new
		fprintf(fp, "%s\n", serialData->buffer);
		//till
    }else{
        printf("Error to read serial port data\n");
    }
}

	fclose(fp); 
}

void closeSerialPort(SerialData* serialData){
    CloseHandle(serialData->handle);
}

int main(){
    SerialData serialData;
    initSerialPort(&serialData);
    configureSerialPort(&serialData);
    readData(&serialData);
    closeSerialPort(&serialData);

    return 0;
}
