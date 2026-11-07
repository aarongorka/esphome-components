# lcd_pcf8574_dynamic

`lcd_pcf8574` with runtime-redefinable custom characters.

> [!WARNING]
> 100% slop coded

```yaml
external_components:
  - source: github://aarongorka/esphome-components
    components: [lcd_pcf8574_dynamic]

display:
  - platform: lcd_pcf8574_dynamic
    dimensions: 16x2
    user_characters:
      - position: 0
        data: [0x00, 0x0a, 0x1f, 0x1f, 0x0e, 0x04, 0x00, 0x00]
    lambda: |-
      it.print("\x08");
      id(lcd).set_custom_char(0, {0x04, 0x0e, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x00});
```

`set_custom_char(location, {8 rows})` takes effect on the next redraw.

Redraws write only character cells that differ from the previous frame.
