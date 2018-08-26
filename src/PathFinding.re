type edge = (string, string, float);
type path = array(string);
type graph = array(edge);
type color = float;
type bitmap = array(array(color));

[@bs.deriving jsConverter]
type terrain =
  | [@bs.as 2] Grassland /* Gul */
  | [@bs.as 0] Forest /* Grøn */
  | [@bs.as 10] Mountain /* Lyserød */
  | [@bs.as 5] Hills /* Rød */
  | [@bs.as 4] Road /* Grøn */
  | [@bs.as 1] Water /* Blå */
  | [@bs.as 8] Swamp; /* Turkis */

let terrainToWeight = t =>
  switch (t) {
  | Grassland => 2.0
  | Forest => 4.0
  | Mountain => 5.0
  | Hills => 3.0
  | Road => 1.0
  | Water => 30.0
  | Swamp => 6.0
  };

[@bs.module "./js/Dijkstra.js"]
external dijkstra : (graph, string, string) => (path, float) = "dijkstra";

let g = [|("a", "b", 7.0), ("b", "c", 9.0)|];
let (path, length) = dijkstra(g, "a", "c");