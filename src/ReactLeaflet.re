let fromOption = Js.Undefined.fromOption;

module LatLng = {
  include LeafletRe.LatLng;
  let make = LeafletRe.latLng;
};

module LatLngBounds = {
  include LeafletRe.LatLngBounds;
  let make = LeafletRe.latLngBounds;
  [@bs.send] external contains : (t, LatLng.t) => bool = "";
};

type zoomOption =
  | Yes
  | No
  | Center;

let zoomOptionConvert: option(zoomOption) => Js.Types.tagged_t =
  optZoom =>
    switch (optZoom) {
    | Some(zoom) =>
      switch (zoom) {
      | Yes => Js.Types.JSTrue
      | No => Js.Types.JSFalse
      | Center => Js.Types.JSString("center")
      }
    | None => Js.Types.JSUndefined
    };

module ImageOverlay = {
  [@bs.module "react-leaflet"]
  external reactClass : ReasonReact.reactClass = "ImageOverlay";
  let make =
      (
        ~url: string,
        ~bounds: LatLngBounds.t,
        ~opacity: option(float)=?,
        ~zIndex: option(float)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "url": url,
        "bounds": bounds,
        "opacity": fromOption(opacity),
        "zIndex": fromOption(zIndex),
      },
      children,
    );
};

module Polyline = {
  [@bs.module "react-leaflet"]
  external reactClass : ReasonReact.reactClass = "Polyline";
  [@bs.deriving abstract]
  type jsProps = {
    positions: array(LatLng.t),
  };
  let make = (~positions, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~positions),
      children,
    );
};



module MouseEvent = {
  /* Unimplemented properties: originalEvent, sourceTarget, and target */
  type t;
  [@bs.get] external containerPoint : t => LeafletRe.Point.t = "";
  [@bs.get] external layerPoint : t => LeafletRe.Point.t = "";
  [@bs.get] external latLng : t => LatLng.t = "latlng";
};

module Marker = {
  [@bs.module "react-leaflet"]
  external reactClass : ReasonReact.reactClass = "Marker";
  [@bs.deriving abstract]
  type jsProps = {
    position: LatLng.t,
    [@bs.optional]
    draggable: bool,
    /*[@bs.optional] icon: Leaflet.Icon (optional) Unimplemented */
    [@bs.optional]
    zIndexOffset: float,
    [@bs.optional]
    opacity: float,
  };
  let make = (~position, ~draggable=?, ~zIndexOffset=?, ~opacity=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~position, ~draggable?, ~zIndexOffset?, ~opacity?, ()),
      children,
    );
};

module Map = {
  [@bs.module "react-leaflet"]
  external reactClass : ReasonReact.reactClass = "Map";
  [@bs.deriving abstract]
  type jsProps = {
    [@bs.optional]
    animate: bool,
    [@bs.optional]
    bounds: LatLngBounds.t,
    [@bs.optional]
    boxZoom: bool,
    [@bs.optional]
    center: LatLng.t,
    [@bs.optional]
    className: string,
    [@bs.optional]
    doubleClickZoom: zoomOption,
    [@bs.optional]
    dragging: bool,
    [@bs.optional]
    id: string,
    [@bs.optional]
    keyboard: bool,
    [@bs.optional]
    maxBounds: LatLngBounds.t,
    [@bs.optional]
    onClick: MouseEvent.t => unit,
    /* [@bs.optional] *~onViewportChange: int => unit, [> Unimplemented <]*/
    /* [@bs.optional] *~onViewportChanged: int => unit, [> Unimplemented <]*/
    [@bs.optional]
    scrollWheelZoom: zoomOption,
    /* [@bs.optional] *~style: int, [> Unimplemented <]*/
    [@bs.optional]
    tap: bool,
    [@bs.optional]
    touchZoom: zoomOption,
    [@bs.optional]
    useFlyTo: bool,
    [@bs.optional]
    viewport: int,
    [@bs.optional]
    whenReady: unit => unit,
    [@bs.optional]
    zoom: float,
  };
  let make =
      (
        ~animate=?,
        ~bounds=?,
        ~boxZoom=?,
        ~center=?,
        ~className=?,
        ~doubleClickZoom=?,
        ~dragging=?,
        ~id=?,
        ~keyboard=?,
        ~maxBounds=?,
        ~onClick=?,
        ~scrollWheelZoom=?,
        ~tap=?,
        ~touchZoom=?,
        ~useFlyTo=?,
        ~viewport=?,
        ~whenReady=?,
        ~zoom=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        jsProps(
          ~animate?,
          ~bounds?,
          ~boxZoom?,
          ~center?,
          ~className?,
          ~doubleClickZoom?,
          ~dragging?,
          ~id?,
          ~keyboard?,
          ~maxBounds?,
          ~onClick?,
          ~scrollWheelZoom?,
          ~tap?,
          ~touchZoom?,
          ~useFlyTo?,
          ~viewport?,
          ~whenReady?,
          ~zoom?,
          (),
        ),
      children,
    );
};
