/** \file
 * \brief iupval control.
 *
 * See Copyright Notice in iup.h
 * $Id: iupval.h,v 1.7 2004/06/08 20:46:13 scuri Exp $
 */
 
#ifndef __IUPVAL_H 
#define __IUPVAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* callbacks */
#ifndef ICTL_MOUSEMOVE_CB
#define ICTL_MOUSEMOVE_CB "MOUSEMOVE_CB"
#endif

#ifndef ICTL_BUTTON_PRESS_CB 
#define ICTL_BUTTON_PRESS_CB "BUTTON_PRESS_CB"
#endif

#ifndef ICTL_BUTTON_RELEASE_CB
#define ICTL_BUTTON_RELEASE_CB "BUTTON_RELEASE_CB"
#endif

/* Atributos */
#ifndef ICTL_HORIZONTAL
#define ICTL_HORIZONTAL "HORIZONTAL"
#endif

#ifndef ICTL_VERTICAL
#define ICTL_VERTICAL "VERTICAL"
#endif

#ifndef ICTL_SHOWTICKS
#define ICTL_SHOWTICKS "SHOWTICKS"
#endif

Ihandle *IupVal(char *);
void IupValOpen(void);

#ifdef __cplusplus
}
#endif

#endif
