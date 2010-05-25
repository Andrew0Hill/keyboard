/*
                    The HumbleHacker Keyboard Project
                 Copyright � 2008-2010, David Whetstone
               david DOT whetstone AT humblehacker DOT com

  This file is a part of The HumbleHacker Keyboard Project.

  The HumbleHacker Keyboard Project is free software: you can redistribute
  it and/or modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  The HumbleHacker Keyboard Project is distributed in the hope that it will
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
  Public License for more details.

  You should have received a copy of the GNU General Public License along
  with The HumbleHacker Keyboard Project.  If not, see
  <http://www.gnu.org/licenses/>.

*/

#ifndef __HIDUSAGETABLES_H__
#define __HIDUSAGETABLES_H__

#define MAKE_USAGE(page,id) (((page)<<10)|(id))
#define USAGE_ID(usage)     (usage&~(0xffff<<10))
#define USAGE_PAGE(usage)   (usage>>10)

#define HID_USAGE_NONE        0UL
#define HID_USAGE_PAGE_CUSTOM 0x3f
#define HID_USAGE_CUSTOM      MAKE_USAGE(HID_USAGE_PAGE_CUSTOM,0)
#define HID_USAGE_PAGE_MACRO  0x3e
#define HID_USAGE_MACRO(x)    MAKE_USAGE(HID_USAGE_PAGE_MACRO,(x))

typedef uint8_t  UsagePage;
typedef uint8_t  UsageID;
typedef enum
{
<% $hid.pages.each do |usagePage| %>
  /* USAGE PAGE:  <%=usagePage.name %> */
#define HID_USAGE_PAGE_<%= normalize_identifier(usagePage.name)%> <%=dec_to_hex(usagePage.id)%>

<%   $hid.usagesByPage[usagePage].each do |usage| %>
  HID_USAGE_<%=normalize_identifier(usage.name)%> = MAKE_USAGE(<%=dec_to_hex(usagePage.id)%>, <%=dec_to_hex(usage.id)%>),
<%   end %>
<% end %>

} Usage;

enum Modifiers
{
  NONE  = 0,
  L_CTL = (1<<0),
  L_SHF = (1<<1),
  L_ALT = (1<<2),
  L_GUI = (1<<3),
  R_CTL = (1<<4),
  R_SHF = (1<<5),
  R_ALT = (1<<6),
  R_GUI = (1<<7),
};

static inline
Modifiers
get_modifier(Usage usage)
{
  switch(usage)
  {
  case HID_USAGE_LEFT_CONTROL:
    return L_CTL;
  case HID_USAGE_LEFT_SHIFT:
    return L_SHF;
  case HID_USAGE_LEFT_ALT:
    return L_ALT;
  case HID_USAGE_LEFT_GUI:
    return L_GUI;
  case HID_USAGE_RIGHT_CONTROL:
    return R_CTL;
  case HID_USAGE_RIGHT_SHIFT:
    return R_SHF;
  case HID_USAGE_RIGHT_ALT:
    return R_ALT;
  case HID_USAGE_RIGHT_GUI:
    return R_GUI;
  default:
    return NONE;
  }
}

#endif /* __HIDUSAGETABLES_H__ */

