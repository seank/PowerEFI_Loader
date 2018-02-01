/*
 * SF2_isp.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: skeys
 */

#include "sf2_isp.h"

#include "src/lib/logging/logger.h"

#include <stdlib.h>

namespace PowerEFI {

SF2isp::SF2isp() {
  // TODO Auto-generated constructor stub

}

SF2isp::~SF2isp() {
  // TODO Auto-generated destructor stub
}

bool SF2isp::load(ISPmode Action_code, UARTinterface *uart_interface, string&
    file_name) {
  DCB dcb;
  HANDLE hCom;
  HANDLE *ptr;
  FILE *fp;
  long size,result,length,address,factor,temp;
  char filename[100];
  char buffer[8192];
  char ret[8];
  char filesize[8];
  BOOL bReadRC;
  static DWORD iBytesRead = -1;
  char Ack[2]="a";
  long returnbytes;
  BOOL fSuccess;
  char pcCommPort[10]="\\\\.\\COM";
  char prevch;
  char crc = 0;
  char Action_code[2];
  if(argc <4)
  {

    printf("Usage for M2S_UARTHost_Loader: M2S_UARTHost_Loader.exe filename comportnumber mode\n");
    printf("ISP modes : mode = 0 -> Authenticate ; mode = 1 -> program ; mode = 2 -> verify\n");

    return 0;
  }
  strcpy(Action_code,argv[3]);
  //printf("mode = %s\n",Action_code);

    if( Action_code[0] != '0' && Action_code[0] != '1' &&  Action_code[0] != '2')
    {
        printf("Usage for M2S_UARTHost_Loader: M2S_UARTHost_Loader.exe filename comportnumber mode\n");
    printf("ISP modes : \nmode = 0 -> Authenticate ; mode = 1 -> program ; mode = 2 -> verify\n");

    return 0;
    }

  strcat(pcCommPort,argv[2]);
  hCom = CreateFile( pcCommPort,
      GENERIC_READ | GENERIC_WRITE,
      0, // must be opened with exclusive-access
      NULL, // no security attributes
      OPEN_EXISTING, // must use OPEN_EXISTING
      0, // not overlapped I/O
      NULL // hTemplate must be NULL for comm devices
  );

  if (hCom == INVALID_HANDLE_VALUE)
  {
    // Handle the error.
    printf ("Cann't open UART port, Please close if the port is open by other application %d.\n", GetLastError());
    return (1);
  }

  // Build on the current configuration, and skip setting the size
  // of the input and output buffers with SetupComm.

  fSuccess = GetCommState(hCom, &dcb);

  if (!fSuccess)
  {
    // Handle the error.
    printf ("Cann't open UART port, Please close if the port is open by other application %d.\n", GetLastError());
    return (2);
  }

  // Fill in DCB: 57,600 bps, 8 data bits, no parity, and 1 stop bit.

  dcb.BaudRate = CBR_57600; // set the baud rate
  dcb.ByteSize = 8; // data size, xmit, and rcv
  dcb.Parity = NOPARITY; // no parity bit
  dcb.StopBits = ONESTOPBIT; // one stop bit

  fSuccess = SetCommState(hCom, &dcb);

  if (!fSuccess)
  {
    // Handle the error.
    printf ("Cann't set the UART port Settings %d.\n", GetLastError());
    return (3);
  }

  printf ("Serial port %s successfully reconfigured.\n", pcCommPort);
  printf("\n\nPlease make sure Smartfusion2 Evaluation kit is running \n");
  printf("Reset the Evaluation Kit board before launching this host loader application\n\n");
  printf("Handshaking with Smartfusion2 Evaluation Kit Started \n");


  SerialPutc(hCom,'h');
  ret[0] = SerialGetc(hCom);
  if (ret[0] == 'a')
  {
    SerialPutc(hCom,'n');
  }
  else
  {
    printf("Handshake fail\n");
    printf("Please reset the SmartFusion2 Evaluation Kit Board \n");
    printf("restart this hostloader application with correct perameters \n");
    return 0;

  }

  ret[0] = SerialGetc(hCom);

  if (ret[0] == 'd')
  {
    SerialPutc(hCom,'s');
  }
  else
  {
    printf("Handshake fail\n");
    printf("Please reset the SmartFusion2 Evaluation Kit Board \n");
    printf("restart this hostloader application with correct perameters \n");
    return 0;

  }

  ret[0] = SerialGetc(hCom);

  if (ret[0] == 'h')
  {
    SerialPutc(hCom,'a');
  }
  else
  {
      printf("Handshake fail\n");
    printf("Please reset the SmartFusion2 Evaluation Kit Board \n");
    printf("restart this hostloader application with correct perameters \n");
    return 0;

  }

  ret[0] = SerialGetc(hCom);

  if (ret[0] == 'k')
  {
    SerialPutc(hCom,'e');
  }
  else
  {
    printf("Handshake fail\n");
    printf("Please reset the SmartFusion2 Evaluation Kit Board \n");
    printf("restart this hostloader application with correct perameters \n");
    return 0;

  }
  ret[0] = SerialGetc(hCom);

  if (ret[0] == 'r')
  {
    printf("HAND SHAKE is fine \n");
  }
  else
  {
    printf("Handshake fail\n");
    printf("Please reset the SmartFusion2 Evaluation Kit Board \n");
    printf("restart this hostloader application with correct perameters \n");
    return 0;

  }

  printf("HAND SHAKE is fine \n");

  printf("Sending starting Ack ....\n");
  bWriteRC = WriteFile(hCom, Ack, 1, &iBytesWritten,NULL);
  bReadRC = ReadFile(hCom, ret, 1,&iBytesRead,NULL);

  printf("Sending the ISP operation mode ....\n");
  //send the mode
  ret[0] = SerialGetc(hCom);
  if (ret[0] == 'm')
  {
        SerialPutc(hCom,Action_code[0]);
  }
  strcpy(filename, argv[1]);
  fp = fopen(filename,"rb");
  // obtain file size:
  fseek (fp , 0 , SEEK_END);
  size = ftell (fp);
  rewind (fp);

  printf("Sending the programming file size = %d\n", size);
  ret[0] = SerialGetc(hCom);
  if (ret[0] == 'z')
  {
        _itoa(size,filesize,10);
    bWriteRC = WriteFile(hCom, filesize, 8, &iBytesWritten,NULL);
  }
  //Read the address and return bytes from target and transmit the requested number of bytes from that address to the target.
  //At the target side the data will be stored in internal memory and IAP will programm the FPGA with the stored data from internal memory.

  while(1)
  {
    //read the message from the target.
    bReadRC = ReadFile(hCom, ret, 1,&iBytesRead,NULL);
    //printf("ret = %d\n", ret[0]);
    /*if(ret[0]=='y'&& (address+returnbytes)==size)
    {
      prevch=ret[0];
    //  printf("FPGA array is programmed and enabled.\n");
      continue;

    }
    else if(ret[0]==0&& (address+returnbytes)==size&&prevch=='y')
    {
      printf("error code =%d\n",ret[0]);
      bWriteRC = WriteFile(hCom, Ack, 1, &iBytesWritten,NULL);
      return (0);
    }
    else if(ret[0]=='f')
    {
      //printf("CRC Check Fail, Please veirfy the PDB file. Reset the Target IAP loader\n");
      return (0);
    }
    else*/
        if( Action_code[0] == '2')
        {
            if(ret[0] == 'p')
            {
                 printf("\nISP Verification completed successfully\n");
                 return (0);
            }
            else if(ret[0] == 'q')
            {
                printf("\nISP Verification failed");
                temp = 0;
                bReadRC =ReadFile(hCom, (char *)&temp, 8,&iBytesRead,NULL);
                printf(" with error code = %d\n",temp);
                return (0);
             }
        }
        else if( Action_code[0] == '0')
        {
            if(ret[0] == 'p')
            {
                 printf("\nISP Authentication completed successfully\n");
                 return (0);
            }
            else if(ret[0] == 'q')
            {
                printf("\nISP Authentication failed");
                temp = 0;
                bReadRC =ReadFile(hCom, (char *)&temp, 8,&iBytesRead,NULL);
                printf(" with error code = %d\n",temp);
                return (0);
             }

         }

        if(ret[0]!='b')
      continue;


    if(bReadRC==0)
    {
      printf("No transction started from the target.Begin transaction Ack 'b' fails\n");
    }

    printf("============Begin transaction Ack '%s' is received from the target=============\n",ret);
    //send Ack message to the target as an acknowledgement for receiving the begin transaction Ack 'b'.
    bWriteRC = WriteFile(hCom, Ack, 1, &iBytesWritten,NULL);
    if(bWriteRC==0)
    {
      printf("Sending Ack message 'a' fails for an acknowledgement of receiving the begin transaction Ack 'b'\n");
    }
    //read address from target
    bReadRC =ReadFile(hCom, (char *)&temp, 8,&iBytesRead,NULL);
    address = temp*8;
    if(bReadRC==0)
    {
      printf("Read address transaction fails from the target\n");
    }
    printf("Requested address from the target =%d\n", address);
    //send an Ack to the target as an acknowledgment for receiving the address
    bWriteRC = WriteFile(hCom, Ack, 1, &iBytesWritten,NULL);
    if(bWriteRC==0)
    {
      printf("Sending Ack message fails for the received address\n");
    }
    //read returnbytes from target
    bReadRC =ReadFile(hCom, (char *)&returnbytes, 4,&iBytesRead,NULL);
    if(bReadRC==0)
    {
      printf("Read number of returnbytes transcation fails from the target\n");
    }
    printf("Requested returnbytes from the target =%d\n", returnbytes);
    //send an Ack to the target as an acknowledgment for receiving the returnbytes
    bWriteRC = WriteFile(hCom, Ack, 1, &iBytesWritten,NULL);
    if(bWriteRC==0)
    {
      printf("Sending Ack message fails for the received returnbytes\n");
    }
    //set the file pointer to the requested address
    fseek (fp , address , SEEK_SET);
    //read the requested number of bytes from the file into buffer
    result = fread (buffer,1,returnbytes,fp);

    printf("bytes read from the file=%d\n", result);
    //printf("requested bytes from the the target =%d\n", returnbytes);
        printf("Remaining bytes =%d\n", size - address-returnbytes);
    if (result != returnbytes)
    {
      printf("Can't open Input file: Please check the path of the file: Reading error\n");
      exit (3);
    }

    //send the requested data to the target
    bWriteRC = WriteFile(hCom, buffer, returnbytes, &iBytesWritten,NULL);
    printf("Sending the data to the target...............................................\n");
    //read an Ack from the target to ensure that the whole data is received by the target
    bReadRC = ReadFile(hCom, ret, 1,&iBytesRead,NULL);
    if(bReadRC==0)
    {
      printf("Read Ack operation fail from target for the requested bytes\n");
    }
    //CRC check
       factor = 1;
           crc = 0;
           while((returnbytes-1)/factor)
           {
              crc = crc^buffer[factor];
              factor = factor*2;
           }
          bWriteRC = WriteFile(hCom, &crc, 1, &iBytesWritten,NULL);
          bReadRC = ReadFile(hCom, ret, 1,&iBytesRead,NULL);
      if(bReadRC==0)
      {
      printf("Read Ack operation fail from target for the requested bytes\n");
           }
           else
           printf("End of one transaction:Ack '%s' received from target for the data from the host\n",ret);

        //CRC check ends
    fclose(fp);
    if(address+returnbytes == size)
       {
        if(Action_code[0] == '1')
        {
             printf("\n*********ISP Programming completed successfully*******\n");
             return (0);
        }
        bReadRC = ReadFile(hCom, ret, 1,&iBytesRead,NULL);
    if(ret[0]=='p')
        {
            if(Action_code[0] == '0')
            printf("\n*********ISP Authentication completed successfully*******\n");
            else if(Action_code[0] == '2')
            printf("\n*********ISP Verification completed successfully*******\n");
            return (0);
        }
        else if(ret[0]=='q')
        {
            if(Action_code[0] == '0')
            printf("\n*********ISP Authentication failed\n");
            else if(Action_code[0] == '2')
            printf("\n*********ISP Verification failed\n");
            temp = 0;
            bReadRC =ReadFile(hCom, (char *)&temp, 8,&iBytesRead,NULL);
            printf(" with error code = %d\n",temp);

            return (0);
        }
        }
    if(returnbytes == 0 && address >= size )
    {

            printf("\n*********ISP Action completed*******\n");

              return (0);

        }
    fp = fopen(filename,"rb");
  }
  printf("Some thing is Wrong with the target,the control shouldn't come here\n");

  return (0);

}}


}
