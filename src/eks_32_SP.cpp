/**
 *   Programeksempel nr 32 - SP.
 *
 *   Eksemplet angir EN implementasjon av SP (Shortest-Path)
 *   - Dijkstras algoritme, på en (liten) vektet graf.
 *
 *   Algoritme/virkemåte:
 *     "Identisk" til Prim's algoritme, bare at avstanden fra node nr.'i'
 *     via node nr.'j' til node nr.'k' er avstanden fra nr.'j' til nr.'k'
 *     PLUSS minimumsavstanden fra nr.'i' til nr.'j'.
 *
 *   Orden ( O(...)):
 *        Samme som MST  (se EKS_31_MST.CPP).
 *
 *   @file     EKS_32_SP.CPP
 *   @author   Frode Haug, NTNU
 */


// *********************************************************************
// **                                                                 **
// **   KODEN ER HELT IDENTISK TIL  EKS_31_MST.CPP, BARE AT           **
// **   FØR LINJE NR.122 SMETTES FØLGENDE KODELINJE INN (!!!):        **
// **                                                                 **
// **             vekt += gKantVekt[nr];                              **
// **                                                                 **
// *********************************************************************


#include <iostream>


int main()  {

  std::cout << "\n\nSe kommentarene i dette programmets kildekode.\n\n";

  return 0;
}
