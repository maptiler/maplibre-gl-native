#include <mbgl/test/util.hpp>

#include <mbgl/util/logging.hpp>
#include <mbgl/util/mapbox.hpp>
#include <mbgl/util/constants.hpp>
#include <mbgl/util/tileset.hpp>
#include <mbgl/util/tile_server_options.hpp>
#include <mbgl/storage/resource_options.hpp>
#include <stdexcept>

using namespace mbgl;
using SourceType = mbgl::style::SourceType;

namespace mapboxFixture {
const TileServerOptions tileServerOptions = TileServerOptions::MapboxConfiguration();
} // namespace fixture

TEST(Mapbox, SourceURL) {
    EXPECT_EQ(
        "https://api.mapbox.com/v4/user.map.json?access_token=key&secure",
        mbgl::util::mapbox::normalizeSourceURL(mapboxFixture::tileServerOptions, "mapbox://user.map", "key"));
    EXPECT_EQ(
        "https://api.example.com/v4/user.map.json?access_token=key&secure",
              mbgl::util::mapbox::normalizeSourceURL(TileServerOptions(mapboxFixture::tileServerOptions).withBaseURL("https://api.example.com"), "mapbox://user.map", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/user.map.json?access_token=key&secure&style=mapbox://styles/mapbox/streets-v9@0",
        mbgl::util::mapbox::normalizeSourceURL(mapboxFixture::tileServerOptions, "mapbox://user.map?style=mapbox://styles/mapbox/streets-v9@0", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/user.map.json?access_token=key&secure",
        mbgl::util::mapbox::normalizeSourceURL(mapboxFixture::tileServerOptions, "mapbox://user.map?", "key"));
    EXPECT_EQ(
        "http://path",
        mbgl::util::mapbox::normalizeSourceURL(mapboxFixture::tileServerOptions, "http://path", "key"));
    EXPECT_THROW(
        mbgl::util::mapbox::normalizeSourceURL(mapboxFixture::tileServerOptions, "mapbox://user.map", ""),
        std::runtime_error);
}

TEST(Mapbox, GlyphsURL) {
    EXPECT_EQ(
        "https://api.mapbox.com/fonts/v1/boxmap/Comic%20Sans/0-255.pbf?access_token=key",
        mbgl::util::mapbox::normalizeGlyphsURL(mapboxFixture::tileServerOptions, "mapbox://fonts/boxmap/Comic%20Sans/0-255.pbf", "key"));
    EXPECT_EQ(
        "https://api.example.com/fonts/v1/boxmap/Comic%20Sans/0-255.pbf?access_token=key",
              mbgl::util::mapbox::normalizeGlyphsURL(TileServerOptions(mapboxFixture::tileServerOptions).withBaseURL("https://api.example.com"), "mapbox://fonts/boxmap/Comic%20Sans/0-255.pbf", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/fonts/v1/boxmap/{fontstack}/{range}.pbf?access_token=key",
        mbgl::util::mapbox::normalizeGlyphsURL(mapboxFixture::tileServerOptions, "mapbox://fonts/boxmap/{fontstack}/{range}.pbf", "key"));
    EXPECT_EQ(
        "http://path",
        mbgl::util::mapbox::normalizeGlyphsURL(mapboxFixture::tileServerOptions, "http://path", "key"));
    EXPECT_EQ(
        "mapbox://path",
        mbgl::util::mapbox::normalizeGlyphsURL(mapboxFixture::tileServerOptions, "mapbox://path", "key"));
}

TEST(Mapbox, StyleURL) {
    EXPECT_EQ(
        "mapbox://foo",
        mbgl::util::mapbox::normalizeStyleURL(mapboxFixture::tileServerOptions, "mapbox://foo", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/user/style?access_token=key",
        mbgl::util::mapbox::normalizeStyleURL(mapboxFixture::tileServerOptions, "mapbox://styles/user/style", "key"));
    EXPECT_EQ(
        "https://api.example.com/styles/v1/user/style?access_token=key",
              mbgl::util::mapbox::normalizeStyleURL(TileServerOptions(mapboxFixture::tileServerOptions).withBaseURL("https://api.example.com"), "mapbox://styles/user/style", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/user/style/draft?access_token=key",
        mbgl::util::mapbox::normalizeStyleURL(mapboxFixture::tileServerOptions, "mapbox://styles/user/style/draft", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/user/style?access_token=key&shave=true",
        mbgl::util::mapbox::normalizeStyleURL(mapboxFixture::tileServerOptions, "mapbox://styles/user/style?shave=true", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/user/style?access_token=key",
        mbgl::util::mapbox::normalizeStyleURL(mapboxFixture::tileServerOptions, "mapbox://styles/user/style?", "key"));
    EXPECT_EQ(
        "http://path",
        mbgl::util::mapbox::normalizeStyleURL(mapboxFixture::tileServerOptions, "http://path", "key"));
}

TEST(Mapbox, SpriteURL) {
    EXPECT_EQ(
        "map/box/sprites@2x.json",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "map/box/sprites@2x.json", "key"));
    EXPECT_EQ(
        "mapbox://foo",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "mapbox://foo", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/mapbox/streets-v8/sprite.json?access_token=key",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "mapbox://sprites/mapbox/streets-v8.json", "key"));
    EXPECT_EQ(
        "https://api.example.com/styles/v1/mapbox/streets-v8/sprite.json?access_token=key",
              mbgl::util::mapbox::normalizeSpriteURL(TileServerOptions(mapboxFixture::tileServerOptions).withBaseURL("https://api.example.com"), "mapbox://sprites/mapbox/streets-v8.json", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/mapbox/streets-v8/sprite@2x.png?access_token=key",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "mapbox://sprites/mapbox/streets-v8@2x.png", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/mapbox/streets-v8/draft/sprite@2x.png?access_token=key",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "mapbox://sprites/mapbox/streets-v8/draft@2x.png", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/styles/v1/mapbox/streets-v11/sprite?access_token=key&fresh=true.png",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions,
            "mapbox://sprites/mapbox/streets-v11?fresh=true.png",
            "key"));
    EXPECT_EQ("mapbox://////", mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "mapbox://////", "key"));
}

TEST(Mapbox, TileURL) {
    EXPECT_EQ(
        "https://api.mapbox.com/v4/a.b/0/0/0.pbf?access_token=key",
        mbgl::util::mapbox::normalizeTileURL(mapboxFixture::tileServerOptions, "mapbox://tiles/a.b/0/0/0.pbf", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/a.b/0/0/0.pbf?access_token=key&style=mapbox://styles/mapbox/streets-v9@0",
        mbgl::util::mapbox::normalizeTileURL(mapboxFixture::tileServerOptions, "mapbox://tiles/a.b/0/0/0.pbf?style=mapbox://styles/mapbox/streets-v9@0", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/a.b/0/0/0.pbf?access_token=key",
        mbgl::util::mapbox::normalizeTileURL(mapboxFixture::tileServerOptions, "mapbox://tiles/a.b/0/0/0.pbf?", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/a.b/0/0/0.png?access_token=key",
        mbgl::util::mapbox::normalizeTileURL(mapboxFixture::tileServerOptions, "mapbox://tiles/a.b/0/0/0.png", "key"));
    EXPECT_EQ(
        "https://api.example.com/v4/a.b/0/0/0.png?access_token=key",
              mbgl::util::mapbox::normalizeTileURL(TileServerOptions(mapboxFixture::tileServerOptions).withBaseURL("https://api.example.com"), "mapbox://tiles/a.b/0/0/0.png", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/a.b/0/0/0@2x.png?access_token=key",
        mbgl::util::mapbox::normalizeTileURL(mapboxFixture::tileServerOptions, "mapbox://tiles/a.b/0/0/0@2x.png", "key"));
    EXPECT_EQ(
        "https://api.mapbox.com/v4/a.b,c.d/0/0/0.pbf?access_token=key",
        mbgl::util::mapbox::normalizeTileURL(mapboxFixture::tileServerOptions, "mapbox://tiles/a.b,c.d/0/0/0.pbf", "key"));
    EXPECT_EQ(
        "http://path",
        mbgl::util::mapbox::normalizeSpriteURL(mapboxFixture::tileServerOptions, "http://path", "key"));
}

TEST(Mapbox, CanonicalURL) {
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://a.tiles.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://b.tiles.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions,"http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf?access_token=key", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions,"https://api.mapbox.cn/v4/a.b/{z}/{x}/{y}.vector.pbf?access_token=key", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b,c.d/{z}/{x}/{y}.vector.pbf",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions,"http://api.mapbox.com/v4/a.b,c.d/{z}/{x}/{y}.vector.pbf?access_token=key", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf?custom=parameter",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions,"http://a.tiles.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf?access_token=key&custom=parameter", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf?custom=parameter",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://a.tiles.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf?custom=parameter&access_token=key", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}.vector.pbf?custom=parameter&second=param",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://a.tiles.mapbox.com/v4/a.b/{z}/{x}/{y}.vector.pbf?custom=parameter&access_token=key&second=param", SourceType::Vector, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}{ratio}.jpg",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.jpg?access_token=key", SourceType::Raster, 256));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}{ratio}.jpg70",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.jpg70?access_token=key", SourceType::Raster, 256));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}@2x.jpg",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.jpg?access_token=key", SourceType::Raster, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}@2x.jpg70",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.jpg70?access_token=key", SourceType::Raster, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}{ratio}.png",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.png", SourceType::Raster, 256));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}{ratio}.png",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.png?access_token=key", SourceType::Raster, 256));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}@2x.png",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.png", SourceType::Raster, 512));
    EXPECT_EQ(
        "mapbox://tiles/a.b/{z}/{x}/{y}@2x.png",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.png?access_token=key", SourceType::Raster, 512));

    // We don't ever expect to see these inputs, but be safe anyway.
    EXPECT_EQ(
        "",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "", SourceType::Raster, 256));
    EXPECT_EQ(
        "http://path",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://path", SourceType::Raster, 256));
    EXPECT_EQ(
        "http://api.mapbox.com/v4/",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/", SourceType::Raster, 256));
    EXPECT_EQ(
        "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}.", SourceType::Raster, 256));
    EXPECT_EQ(
        "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}/.",
        mbgl::util::mapbox::canonicalizeTileURL(mapboxFixture::tileServerOptions, "http://api.mapbox.com/v4/a.b/{z}/{x}/{y}/.", SourceType::Raster, 256));
}

TEST(Mapbox, CanonicalizeRasterTileset) {
    mbgl::Tileset tileset;
    tileset.tiles = {
        "http://a.tiles.mapbox.com/v4/mapbox.satellite/{z}/{x}/{y}.png?access_token=key"
    };

    mbgl::util::mapbox::canonicalizeTileset(mapboxFixture::tileServerOptions, tileset, "mapbox://mapbox.satellite", SourceType::Raster, 256);

    EXPECT_EQ("mapbox://tiles/mapbox.satellite/{z}/{x}/{y}{ratio}.png", tileset.tiles[0]);
}

TEST(Mapbox, CanonicalizeVectorTileset) {
    mbgl::Tileset tileset;
    tileset.tiles = {
        "http://a.tiles.mapbox.com/v4/mapbox.streets/{z}/{x}/{y}.vector.pbf?access_token=key"
    };

    mbgl::util::mapbox::canonicalizeTileset(mapboxFixture::tileServerOptions, tileset, "mapbox://mapbox.streets", SourceType::Vector, 512);

    EXPECT_EQ("mapbox://tiles/mapbox.streets/{z}/{x}/{y}.vector.pbf", tileset.tiles[0]);
}
