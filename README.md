# action-text

A simple UI library providing a centered text element for messages to prompt the player to perform an action, hence "action" text.

![https://i.imgur.com/Z1RRsCc.png](https://i.imgur.com/Z1RRsCc.png)

## Usage

Simply add to your `pawn.json` and include:

```json
{
    "dependencies": ["ScavengeSurvive/action-text"]
}
```

```pawn
#include <action-text>
```

## Testing

To test, simply run the package:

```bash
sampctl package run
```

Then connect to `localhost:7777`.

Trigger `OnPlayerKeyStateChange` to show a demo.
