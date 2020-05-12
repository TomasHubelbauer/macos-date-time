# macOS Date & Time

In macOS, the date and time formatting strings have a UI which allows editing them
by bringing tokens in and out of the format string edit fields. The field is also
editable so constant strings can be intertwined with the tokens which will become
substitued with the actual variable value.

This seems to interact weirdly with the System Preferences > Languages & Region >
General > 24-Hour Time setting. Specifically, in case this setting is ON (so the
AM/PM token should not be included in the time format string) while the AM/PM box
is included in the time format string at the same time, it will remain a part of
it, when it should be removed instead.

Also, in the case of this toggle being OFF (so the token should be included in the
time format string) while at the same time the time format field already including
the AM/PM token, if the token is enclosed in constant string characters, another
one will be appeneded to the final format string. If it is enclosed by other tokens
or white-space, it will be moved to have a space in front of it instead.

This is all very weird, but the main concern is that in case the AM/PM token is
included in the time format string and the 24-Hour Time toggle being ON, the format
string will still include the ` a` token instead of not doing so!

This token is included by default, and when using the default, it will be removed
or added depending on the value of the toggle, but if changed, the toggle will lose
its ability to correctly manipulate these format strings wrecking everything holy.

## Running

`make`

## Results

There are two options for configuring date and time in macOS:

### System Preferences > Date & Time > Clock > Show date and time in menu bar

There are these two settings:

- Use a 24-hour clock
- Show AM/PM

**These settings only apply to the menu bar!**

### System Preferences > Languages & Region > General

There is the **24-Hour Time** setting.

Whether or not the `a` token (for AM/PM) is present in the format string is then
determined according to the following rules:

| Language & Region > General > 24-Hour Time? | Language & Region > General > Advanced > Times includes `AM/PM`? | Actual           | Expected         | Result |
|---------------------------------------------|------------------------------------------------------------------|------------------|------------------|--------|
| Yes                                         | Yes                                                              | `a` preserved    | `a` removed      | NOK    |
| Yes                                         | No                                                               | `a` not appended | `a` not appended | OK     |
| No                                          | Yes                                                              | `a` appended     | `a` preserved    | NOK*   |
| No                                          | No                                                               | `a` appended     | `a` appended     | OK     |

> I have enclosed the AM/PM token in parentheses when added manually in the time
format fields to differentiate them from when the OS adds them due to the 24 hour
format switch being off and them not being in the pattern.

<table>
  <thead>
    <tr>
      <th>Language & Region > General > Advanced > Times Includes `AM/PM`?</th>
      <th>Language & Region > General > 24-Hour Time? **YES**</th>
      <th>Language & Region > General > 24-Hour Time? = **NO**</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>YES</th>
      <td>
        <!-- Language & Region > General > 24-Hour Time YES - Language & Region > General > Advanced > Times includes AM/PM YES -->
        <pre>
time short: "HH-mm(a)"
time medium: "HH-mm-ss(a)"
time long: "HH-mm-ss(a)z"
time full: "HH:mm:ss(a)zzzz"
        </pre>
      </td>
      <td>
        <!-- Language & Region > General > 24-Hour Time NO - Language & Region > General > Advanced > Times includes AM/PM YES -->
        <pre>
time short: "h-mm(a) a"
time medium: "h-mm-ss(a) a"
time long: "h-mm-ss(a)z"
time full: "h:mm:ss(a)zzzz"
        </pre>
      </td>
    </tr>
    <tr>
      <th>NO</th>
      <td>
        <!-- Language & Region > General > 24-Hour Time YES - Language & Region > General > Advanced > Times includes AM/PM NO -->
        <pre>
time short: "HH-mm"
time medium: "HH-mm-ss"
time long: "HH-mm-ssz"
time full: "HH:mm:sszzzz"
        </pre>
      </td>
      <td>
        <!-- Language & Region > General > 24-Hour Time NO - Language & Region > General > Advanced > Times includes AM/PM NO -->
        <pre>
time short: "h-mm a"
time medium: "h-mm-ss a"
time long: "h-mm-ssz"
time full: "h:mm:sszzzz"
        </pre>
      </td>
    </tr>
  </tbody>
</table>

> * Without the parentheses (might this have an effect on whether the token gets preserved or appended?)
> In this case the AM/PM token got moved instead of appended, which is a better result:

<table>
  <thead>
    <tr>
      <th>Language & Region > General > Advanced > Times Includes `AM/PM`?</th>
      <th>Language & Region > General > 24-Hour Time? **YES**</th>
      <th>Language & Region > General > 24-Hour Time? = **NO**</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>YES</th>
      <td>
        <!-- Language & Region > General > 24-Hour Time YES - Language & Region > General > Advanced > Times includes AM/PM YES -->
        <pre>
time short: "HH-mma"
time medium: "HH-mm-ssa"
time long: "HH-mm-ssaz"
time full: "HH:mm:ssazzzz"
        </pre>
      </td>
      <td>
        <!-- Language & Region > General > 24-Hour Time NO - Language & Region > General > Advanced > Times includes AM/PM YES -->
        <pre>
time short: "h-mm a"
time medium: "h-mm-ss a"
time long: "h-mm-ssaz"
time full: "h:mm:ssazzzz"
        </pre>
      </td>
    </tr>
    <tr>
      <th>NO</th>
      <td>
        <!-- Language & Region > General > 24-Hour Time YES - Language & Region > General > Advanced > Times includes AM/PM NO -->
        <pre>
time short: "HH-mm"
time medium: "HH-mm-ss"
time long: "HH-mm-ssz"
time full: "HH:mm:sszzzz"
        </pre>
      </td>
      <td>
        <!-- Language & Region > General > 24-Hour Time NO - Language & Region > General > Advanced > Times includes AM/PM NO -->
        <pre>
time short: "h-mm a"
time medium: "h-mm-ss a"
time long: "h-mm-ssz"
time full: "h:mm:sszzzz"
        </pre>
      </td>
    </tr>
  </tbody>
</table>
