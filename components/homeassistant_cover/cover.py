import esphome.codegen as cg
from esphome.components import cover
import esphome.config_validation as cv
from esphome.const import CONF_ENTITY_ID, CONF_ID, CONF_INTERNAL
from esphome.types import ConfigType

DEPENDENCIES = ["api"]

homeassistant_cover_ns = cg.esphome_ns.namespace("homeassistant_cover")
HomeassistantCover = homeassistant_cover_ns.class_(
    "HomeassistantCover", cover.Cover, cg.Component
)


def _validate_cover_entity(value: str) -> str:
    value = cv.entity_id(value)
    if value.split(".", 1)[0] != "cover":
        raise cv.Invalid(f"Entity ID {value} must be in the 'cover' domain.")
    return value


CONFIG_SCHEMA = (
    cover.cover_schema(HomeassistantCover)
    .extend(
        {
            cv.Required(CONF_ENTITY_ID): _validate_cover_entity,
            cv.Optional(CONF_INTERNAL, default=True): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config: ConfigType) -> None:
    cg.add_define("USE_API_HOMEASSISTANT_SERVICES")
    cg.add_define("USE_API_HOMEASSISTANT_STATES")
    var = await cover.new_cover(config)
    await cg.register_component(var, config)
    cg.add(var.set_entity_id(config[CONF_ENTITY_ID]))
