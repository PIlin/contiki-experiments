
/*
 * copyright Karl Palsson, karlp@tweak.net.au, 2011
 * modified BSD License / apache license
 */

#ifndef __MRF24J40_CONSTANTS_H__
#define __MRF24J40_CONSTANTS_H__


#ifndef BIT
# define BIT(x) (1U << (x))
#endif



// Control registers

#define    MRF_SRG_RXMCR          0x00
#define    MRF_SRG_PANIDL         0x01
#define    MRF_SRG_PANIDH         0x02
#define    MRF_SRG_SADRL          0x03
#define    MRF_SRG_SADRH          0x04
#define    MRF_SRG_EADR0          0x05
#define    MRF_SRG_EADR1          0x06
#define    MRF_SRG_EADR2          0x07
#define    MRF_SRG_EADR3          0x08
#define    MRF_SRG_EADR4          0x09
#define    MRF_SRG_EADR5          0x0A
#define    MRF_SRG_EADR6          0x0B
#define    MRF_SRG_EADR7          0x0C
#define    MRF_SRG_RXFLUSH        0x0D
//#define  MRF_SRG_Reserved       0x0E
//#define  MRF_SRG_Reserved       0x0F
#define    MRF_SRG_ORDER          0x10
#define    MRF_SRG_TXMCR          0x11
#define    MRF_SRG_ACKTMOUT       0x12
#define    MRF_SRG_ESLOTG1        0x13
#define    MRF_SRG_SYMTICKL       0x14
#define    MRF_SRG_SYMTICKH       0x15
#define    MRF_SRG_PACON0         0x16
#define    MRF_SRG_PACON1         0x17
#define    MRF_SRG_PACON2         0x18
//#define  MRF_SRG_Reserved       0x19
#define    MRF_SRG_TXBCON0        0x1A
#define    MRF_SRG_TXNCON         0x1B
#define    MRF_SRG_TXG1CON        0x1C
#define    MRF_SRG_TXG2CON        0x1D
#define    MRF_SRG_ESLOTG23       0x1E
#define    MRF_SRG_ESLOTG45       0x1F
#define    MRF_SRG_ESLOTG67       0x20
#define    MRF_SRG_TXPEND         0x21
#define    MRF_SRG_WAKECON        0x22
#define    MRF_SRG_FRMOFFSET      0x23
#define    MRF_SRG_TXSTAT         0x24
#define    MRF_SRG_TXBCON1        0x25
#define    MRF_SRG_GATECLK        0x26
#define    MRF_SRG_TXTIME         0x27
#define    MRF_SRG_HSYMTMRL       0x28
#define    MRF_SRG_HSYMTMRH       0x29
#define    MRF_SRG_SOFTRST        0x2A
//#define  MRF_SRG_Reserved       0x2B
#define    MRF_SRG_SECCON0        0x2C
#define    MRF_SRG_SECCON1        0x2D
#define    MRF_SRG_TXSTBL         0x2E
//#define  MRF_SRG_Reserved       0x2F
#define    MRF_SRG_RXSR           0x30
#define    MRF_SRG_INTSTAT        0x31
#define    MRF_SRG_INTCON         0x32
#define    MRF_SRG_GPIO           0x33
#define    MRF_SRG_TRISGPIO       0x34
#define    MRF_SRG_SLPACK         0x35
#define    MRF_SRG_RFCTL          0x36
#define    MRF_SRG_SECCR2         0x37
#define    MRF_SRG_BBREG0         0x38
#define    MRF_SRG_BBREG1         0x39
#define    MRF_SRG_BBREG2         0x3A
#define    MRF_SRG_BBREG3         0x3B
#define    MRF_SRG_BBREG4         0x3C
//#define  MRF_SRG_Reserved       0x3D
#define    MRF_SRG_BBREG6         0x3E
#define    MRF_SRG_CCAEDTH        0x3F

#define    MRF_LRG_RFCON0         0x200
#define    MRF_LRG_RFCON1         0x201
#define    MRF_LRG_RFCON2         0x202
#define    MRF_LRG_RFCON3         0x203
//#define  MRF_LRG_Reserved       0x204
#define    MRF_LRG_RFCON5         0x205
#define    MRF_LRG_RFCON6         0x206
#define    MRF_LRG_RFCON7         0x207
#define    MRF_LRG_RFCON8         0x208
#define    MRF_LRG_SLPCAL0        0x209
#define    MRF_LRG_SLPCAL1        0x20A
#define    MRF_LRG_SLPCAL2        0x20B
//#define  MRF_LRG_Reserved       0x20C
//#define  MRF_LRG_Reserved       0x20D
//#define  MRF_LRG_Reserved       0x20E
#define    MRF_LRG_RFSTATE        0x20F
#define    MRF_LRG_RSSI           0x210
#define    MRF_LRG_SLPCON0        0x211
//#define  MRF_LRG_Reserved       0x212
//#define  MRF_LRG_Reserved       0x213
//#define  MRF_LRG_Reserved       0x214
//#define  MRF_LRG_Reserved       0x215
//#define  MRF_LRG_Reserved       0x216
//#define  MRF_LRG_Reserved       0x217
//#define  MRF_LRG_Reserved       0x218
//#define  MRF_LRG_Reserved       0x219
//#define  MRF_LRG_Reserved       0x21A
//#define  MRF_LRG_Reserved       0x21B
//#define  MRF_LRG_Reserved       0x21C
//#define  MRF_LRG_Reserved       0x21D
//#define  MRF_LRG_Reserved       0x21E
//#define  MRF_LRG_Reserved       0x21F
#define    MRF_LRG_SLPCON1        0x220
//#define  MRF_LRG_Reserved       0x221
#define    MRF_LRG_WAKETIMEL      0x222
#define    MRF_LRG_WAKETIMEH      0x223
#define    MRF_LRG_REMCNTL        0x224
#define    MRF_LRG_REMCNTH        0x225
#define    MRF_LRG_MAINCNT0       0x226
#define    MRF_LRG_MAINCNT1       0x227
#define    MRF_LRG_MAINCNT2       0x228
#define    MRF_LRG_MAINCNT3       0x229
//#define  MRF_LRG_Reserved       0x22A
//#define  MRF_LRG_Reserved       0x22B
//#define  MRF_LRG_Reserved       0x22C
//#define  MRF_LRG_Reserved       0x22D
//#define  MRF_LRG_Reserved       0x22E
#define    MRF_LRG_TESTMODE       0x22F
#define    MRF_LRG_ASSOEADR0      0x230
#define    MRF_LRG_ASSOEADR1      0x231
#define    MRF_LRG_ASSOEADR2      0x232
#define    MRF_LRG_ASSOEADR3      0x233
#define    MRF_LRG_ASSOEADR4      0x234
#define    MRF_LRG_ASSOEADR5      0x235
#define    MRF_LRG_ASSOEADR6      0x236
#define    MRF_LRG_ASSOEADR7      0x237
#define    MRF_LRG_ASSOSADR0      0x238
#define    MRF_LRG_ASSOSADR1      0x239
//#define  MRF_LRG_Reserved       0x23A
//#define  MRF_LRG_Reserved       0x23B
//#define  MRF_LRG_Unimplemented  0x23C
//#define  MRF_LRG_Unimplemented  0x23D
//#define  MRF_LRG_Unimplemented  0x23E
//#define  MRF_LRG_Unimplemented  0x23F
#define    MRF_LRG_UPNONCE0       0x240
#define    MRF_LRG_UPNONCE1       0x241
#define    MRF_LRG_UPNONCE2       0x242
#define    MRF_LRG_UPNONCE3       0x243
#define    MRF_LRG_UPNONCE4       0x244
#define    MRF_LRG_UPNONCE5       0x245
#define    MRF_LRG_UPNONCE6       0x246
#define    MRF_LRG_UPNONCE7       0x247
#define    MRF_LRG_UPNONCE8       0x248
#define    MRF_LRG_UPNONCE9       0x249
#define    MRF_LRG_UPNONCE10      0x24A
#define    MRF_LRG_UPNONCE11      0x24B
#define    MRF_LRG_UPNONCE12      0x24C



#define MRF_LRG_RXFIFO 0x300



#define    MRF_I_RXIF     0b00001000
#define    MRF_I_TXNIF    0b00000001


// TXNCON: TRANSMIT NORMAL FIFO CONTROL REGISTER (ADDRESS: 0x1B)
#define  MRF_TXNTRIG    0
#define  MRF_TXNSECEN   1
#define  MRF_TXNACKREQ  2
#define  MRF_INDIRECT   3
#define  MRF_FPSTAT     4

// TXSTAT: TX MAC STATUS REGISTER (ADDRESS: 0x24)
#define  TXNRETRY1  7
#define  TXNRETRY0  6
#define  CCAFAIL    5
#define  TXG2FNT    4
#define  TXG1FNT    3
#define  TXG2STAT   2
#define  TXG1STAT   1
#define  TXNSTAT    0


enum REG_PACON2 // 0x18
{
	TXONT7   =  BIT(0),
	TXONT8   =  BIT(1),
	TXONTS0  =  BIT(2),
	TXONTS1  =  BIT(3),
	TXONTS2  =  BIT(4),
	TXONTS3  =  BIT(5),
	FIFOEN   =  BIT(7),
};

enum REG_SOFTRST // 0x2a
{
	RSTMAC  =  BIT(0),
	RSTBB   =  BIT(1),
	RSTPWR  =  BIT(2),
};

enum REG_TXSTBL // 0x2e
{
	MSIFS0   =  BIT(0),
	MSIFS1   =  BIT(1),
	MSIFS2   =  BIT(2),
	MSIFS3   =  BIT(3),
	RFSTBL0  =  BIT(4),
	RFSTBL1  =  BIT(5),
	RFSTBL2  =  BIT(6),
	RFSTBL3  =  BIT(7),
};

enum REG_INTSTAT // 0x31
{
	TXNIF      =  BIT(0),
	TXG1IF     =  BIT(1),
	TXG2IF     =  BIT(2),
	RXIF       =  BIT(3),
	SECIF      =  BIT(4),
	HSYMTMRIF  =  BIT(5),
	WAKEIF     =  BIT(6),
	SLPIF      =  BIT(7),
};

enum REG_INTCON // 0x32
{
	TXNIE      =  BIT(0),
	TXG1IE     =  BIT(1),
	TXG2IE     =  BIT(2),
	RXIE       =  BIT(3),
	SECIE      =  BIT(4),
	HSYMTMRIE  =  BIT(5),
	WAKEIE     =  BIT(6),
	SLPIE      =  BIT(7),
};

enum REG_BBREG1 // 0x39
{
	RXDECINV  =  BIT(2),
};

enum REG_RFCON1 // 0x201
{
	VCOOPT0  =  BIT(0),
	VCOOPT1  =  BIT(1),
	VCOOPT2  =  BIT(2),
	VCOOPT3  =  BIT(3),
	VCOOPT4  =  BIT(4),
	VCOOPT5  =  BIT(5),
	VCOOPT6  =  BIT(6),
	VCOOPT7  =  BIT(7),
};

enum REG_RFCON2 // 0x202
{
	PPLEN  =  BIT(7),
};

enum REG_RFCON6 // 0x206
{
	BATEN   =  BIT(3),
	MRECVR  =  BIT(4),
	TXFIL   =  BIT(7),
};

enum REG_RFCON7 // 0x207
{
	SLPSCKSEL0  =  BIT(6),
	SLPCLKSEL1  =  BIT(7),
};

enum REG_RFCON8 // 0x208
{
	RFVCO  =  BIT(4),
};

enum REG_SLPCON0 // 0x211
{
	SLPCKEN  =  BIT(0),
	INTEDGE  =  BIT(1),
};

enum REG_SLPCON1 // 0x220
{
	SLPCLKDIV0  =  BIT(0),
	SLPCLKDIV1  =  BIT(1),
	SLPCLKDIV2  =  BIT(2),
	SLPCLKDIV3  =  BIT(3),
	SLPCLKDIV4  =  BIT(4),
	CLKOUTEN    =  BIT(5),

};


#endif // __MRF24J40_CONSTANTS_H__