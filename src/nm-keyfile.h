/*
 * Copyright (C) 2021 Canonical, Ltd.
 * Author: Lukas Märdian <slyon@ubuntu.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* YAML emitter */
#define YAML_MAPPING_OPEN(event, emitter) \
{ \
    yaml_mapping_start_event_initialize(&event, NULL, (yaml_char_t *)YAML_MAP_TAG, 1, YAML_ANY_MAPPING_STYLE); \
    if (!yaml_emitter_emit(&emitter, &event)) goto error; \
}
#define YAML_MAPPING_CLOSE(event, emitter) \
{ \
    yaml_mapping_end_event_initialize(&event); \
    if (!yaml_emitter_emit(&emitter, &event)) goto error; \
}
#define YAML_SCALAR_PLAIN(event, emitter, scalar) \
{ \
    yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *)YAML_STR_TAG, (yaml_char_t *)scalar, strlen(scalar), 1, 0, YAML_PLAIN_SCALAR_STYLE); \
    if (!yaml_emitter_emit(&emitter, &event)) goto error; \
}
/* Implicit plain and quoted tags, double quoted style */
#define YAML_SCALAR_QUOTED(event, emitter, scalar) \
{ \
    yaml_scalar_event_initialize(&event, NULL, (yaml_char_t *)YAML_STR_TAG, (yaml_char_t *)scalar, strlen(scalar), 1, 1, YAML_DOUBLE_QUOTED_SCALAR_STYLE); \
    if (!yaml_emitter_emit(&emitter, &event)) goto error; \
}

/* Some utils for the NetworkManager YAML backend */
gboolean netplan_render_yaml_from_nm_keyfile(GKeyFile* kf, const char* rootdir);
