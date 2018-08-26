type edge = (string, string, float);
type path = array(string);
type graph = array(edge);
type color = float;
type bitmap = array(array(color));

/* Variant constructors MUST preserve ordering. Only add at end */
[@bs.deriving jsConverter]
type terrain =
  | [@bs.as 0] Forest /* Grøn */
  | [@bs.as 1] Water /* Blå */
  | [@bs.as 2] Grassland /* Gul */
  | [@bs.as 3] Nope3 /* Gul */
  | [@bs.as 4] Road /* Grøn */
  | [@bs.as 5] Hills /* Rød */
  | [@bs.as 6] Nope6 /* Gul */
  | [@bs.as 7] Nope7 /* Gul */
  | [@bs.as 8] Swamp /* Turkis */
  | [@bs.as 9] Nope9 /* Gul */
  | [@bs.as 10] Mountain /* Lyserød */
  | [@bs.as 11] Impassable;

let terrainToWeight = t =>
  switch (t) {
  | Grassland => 2.0
  | Forest => 4.0
  | Mountain => 5.0
  | Hills => 3.0
  | Road => 1.0
  | Water => 30.0
  | Swamp => 6.0
  | Impassable => 99999999999.0
  };

[@bs.module "./js/terrain.js"] external mapData : array(array(terrain)) = "";

[@bs.module "./js/Dijkstra.js"]
external dijkstra : (graph, string, string) => (path, float) = "dijkstra";

let g = [|("a", "b", 7.0), ("b", "c", 9.0)|];
let (path, length) = dijkstra(g, "a", "c");
