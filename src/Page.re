open ReactLeaflet;

let outerBounds =
  LeafletRe.latLngBounds(
    ReactLeaflet.LatLng.make((0.0, 0.0)),
    ReactLeaflet.LatLng.make((1.0, 1.0)),
  );

type routePick =
  | NoSelection
  | Start(ReactLeaflet.LatLng.t)
  | StartEnd(ReactLeaflet.LatLng.t, ReactLeaflet.LatLng.t);

type state = {
  picking: bool,
  pick: routePick,
};

let mapScale = 1000.0;

/* The Leaflet distance function calculates realworld actual distance between
   lat-long coordinates. This just treats lat-long as coordinates, and
   calculates raw distance */
let rawDistance = (p1, p2) =>
  ReactLeaflet.LatLng.(
    sqrt((lat(p1) -. lat(p2)) ** 2.0 +. (lng(p1) -. lng(p2)) ** 2.0)
  );

type action =
  | PickPosition(ReactLeaflet.LatLng.t)
  | ClearSelection
  | StartPicking;

let component = ReasonReact.reducerComponent("Page");

let make = _children => {
  ...component,
  initialState: () => {picking: false, pick: NoSelection},
  reducer: (action: action, state: state) =>
    switch (action) {
    | ClearSelection =>
      ReasonReact.Update({picking: false, pick: NoSelection})
    | StartPicking => ReasonReact.Update({picking: true, pick: NoSelection})
    | PickPosition(position) =>
      let newPick =
        switch (state.pick) {
        | NoSelection => Start(position)
        | Start(startPos) => StartEnd(startPos, position)
        | StartEnd(startPos, _end) => StartEnd(startPos, position)
        };
      ReasonReact.Update({...state, pick: newPick});
    },
  render: self => {
    let pickMarkers =
      switch (self.state.pick) {
      | NoSelection => []
      | Start(position) => [<Marker position />]
      | StartEnd(pStart, pEnd) => [
          <Marker position=pStart />,
          <Marker position=pEnd />,
          <Polyline positions=[|pStart, pEnd|] />,
        ]
      };
    let mapChildren = [
      <ImageOverlay
        url="https://orig00.deviantart.net/6fdc/f/2010/251/8/6/magus_for_talisman_by_feliciacano-d2yakqt.jpg"
        bounds=outerBounds
      />,
      ...pickMarkers,
    ];
    <div>
      <button onClick={_event => self.send(StartPicking)}>
        {ReasonReact.string({js|Vælg|js})}
      </button>
      <button onClick={_event => self.send(ClearSelection)}>
        {ReasonReact.string({js|Ryd valg|js})}
      </button>
      <Map
        id="mapid"
        dragging=true
        bounds=outerBounds
        doubleClickZoom=ReactLeaflet.Center
        onClick={
          x => {
            let position = ReactLeaflet.MouseEvent.latLng(x);
            if (self.state.picking
                && LatLngBounds.contains(outerBounds, position)) {
              self.send(PickPosition(position));
            };
          }
        }>
        mapChildren
      </Map>
      {
        switch (self.state.pick) {
        | StartEnd(pStart, pEnd) =>
          <div>
            {ReasonReact.string("Distance mellem punkter: ")}
            {
              ReasonReact.string(
                string_of_float(rawDistance(pStart, pEnd) *. mapScale),
              )
            }
          </div>
        | _ => ReasonReact.null
        }
      }
    </div>;
  },
};
