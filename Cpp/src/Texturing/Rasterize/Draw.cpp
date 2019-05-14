//
// Created by revetoon on 5/12/19.
//

#include "Draw.hh"
#include "Span.hh"

uint8_t *Draw::drawTriangle(uint8_t *pxls,
                            double x1, double y1,
                            const Color &col1,
                            double x2, double y2,
                            const Color &col2,
                            double x3, double y3,
                            const Color &col3,
                            int width, int height,
                            int colorCount, double ratio) {


    // 1. create edges
    // 2. sort edges
    // 3. create spans
    // 4. draw spans

    std::vector<Edge> edges = std::vector<Edge>{
            Edge(x1 * ratio, y1 * ratio, x2 * ratio, y2 * ratio, col1, col2),
            Edge(x2 * ratio, y2 * ratio, x3 * ratio, y3 * ratio, col2, col3),
            Edge(x3 * ratio, y3 * ratio, x1 * ratio, y1 * ratio, col3, col1),
    };

    double longestSize = 0;
    int longestIdx = 0;

    for (int i = 0; i < edges.size(); ++i) {
        double len = edges[i].y2 - edges[i].y1;
        if (len > longestSize) {
            longestIdx = i;
            longestSize = len;
        }
    }

    int edIdx2 = (longestIdx + 1) % edges.size();
    int edIdx3 = (longestIdx + 2) % edges.size();

    drawSpan(edges[longestIdx], edges[edIdx2], pxls, width, colorCount);
    drawSpan(edges[longestIdx], edges[edIdx3], pxls, height, colorCount);

    return pxls;
}

void Draw::drawSpan(const Edge &e1, const Edge &e2, uint8_t *img, int w, int colorCount) {

    // calc Y size of e1
    double e1ySize = (e1.y2 - e1.y1);
    if(e1ySize == 0.0f)
        return;

    // calc Y size of e2
    double e2ySize = (e2.y2 - e2.y1);
    if(e2ySize == 0.0f)
        return;

    double e1xSize = (e1.x2 - e1.x1);
    double e2xSize = (e2.x2 - e2.x1);
    Color e1coldiff = (e1.col2 - e1.col1);
    Color e2coldiff = (e2.col2 - e2.col1);


    double factore1 = (e2.y1 - e1.y1) / e1ySize;
    double stepe1 = 1.0 / e1ySize;
    double factore2 = 0.0;
    double stepe2 = 1.0 / e2ySize;

    for (int y = e2.y1; y < e2.y2; ++y) {
        // create and draw a span
        Span sp = Span(
                e1.x1 + (e1xSize * factore1),
                e2.x1 + (e2xSize * factore2),
                e1.col1 + (e1coldiff * factore1),
                e2.col1 + (e2coldiff * factore2)
            );
        // TODO draw span on img
        sp.draw(y, img, w, colorCount);
        factore1 += stepe1;
        factore2 += stepe2;
    }
}

uint8_t *
Draw::drawTriangle(Texture &tex, double x1, double y1, double x2, double y2, double x3, double y3, double ratio) {
    return drawTriangle(tex.getUnderlyingPixels(),
                        x1 * ratio, y1 * ratio, Color::white(),
                        x2 * ratio, y2 * ratio, Color::white(),
                        x3 * ratio, y3 * ratio, Color::white(),
                        tex.getWidth(), tex.getHeight(), tex.getColorCount());
}

uint8_t *Draw::drawTriangle(Texture &tex, const RasterPoint &p1, const RasterPoint &p2, const RasterPoint &p3, double ratio) {
    return drawTriangle(tex.getUnderlyingPixels(),
                        p1.x * ratio, p1.y * ratio, p1.col,
                        p2.x * ratio, p2.y * ratio, p2.col,
                        p3.x * ratio, p3.y * ratio, p3.col,
                        tex.getWidth(), tex.getHeight(), tex.getColorCount());
}
