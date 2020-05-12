# macOS Date & Time

In macOS, TODO

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
