// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_WEB_CONTENTS_PREFERENCES_H_
#define ATOM_BROWSER_WEB_CONTENTS_PREFERENCES_H_

#include <string>
#include <vector>

#include "base/values.h"
#include "content/public/browser/web_contents_user_data.h"

namespace base {
class CommandLine;
}

namespace content {
struct WebPreferences;
}

namespace mate {
class Dictionary;
}

namespace atom {

// Stores and applies the preferences of WebContents.
class WebContentsPreferences
    : public content::WebContentsUserData<WebContentsPreferences> {
 public:
  // Get WebContents according to process ID.
  // FIXME(zcbenz): This method does not belong here.
  static content::WebContents* GetWebContentsFromProcessID(int process_id);

  // Get self from WebContents.
  static WebContentsPreferences* From(content::WebContents* web_contents);
  // Get self from procese ID.
  static WebContentsPreferences* From(int process_id);

  // Append command paramters according to |web_contents|'s preferences.
  static void AppendExtraCommandLineSwitches(
      content::WebContents* web_contents, base::CommandLine* command_line);

  // Modify the WebPreferences according to |web_contents|'s preferences.
  static void OverrideWebkitPrefs(
      content::WebContents* web_contents, content::WebPreferences* prefs);

  WebContentsPreferences(content::WebContents* web_contents,
                         const mate::Dictionary& web_preferences);
  ~WebContentsPreferences() override;

  // A simple way to know whether a Boolean property is enabled.
  bool IsEnabled(const base::StringPiece& name, bool default_value = false);

  // $.extend(|web_preferences|, |new_web_preferences|).
  void Merge(const base::DictionaryValue& new_web_preferences);

  // Returns the web preferences.
  base::DictionaryValue* dict() { return &dict_; }
  const base::DictionaryValue* dict() const { return &dict_; }

 private:
  friend class content::WebContentsUserData<WebContentsPreferences>;

  // Get preferences value as integer possibly coercing it from a string
  bool GetInteger(const std::string& attributeName, int* intValue);

  static std::vector<WebContentsPreferences*> instances_;

  content::WebContents* web_contents_;
  base::DictionaryValue dict_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsPreferences);
};

}  // namespace atom

#endif  // ATOM_BROWSER_WEB_CONTENTS_PREFERENCES_H_
