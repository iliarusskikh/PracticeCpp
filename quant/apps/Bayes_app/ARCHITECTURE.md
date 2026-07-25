# Architecture

## Framework choice: Streamlit + Plotly

Evaluated against the build criteria (speed to polished reactive UI, chart quality,
quant-desk fit, slider-driven workflow):

| Criterion | Streamlit + Plotly | Dash + Plotly | PySide6 / PyQt6 |
|---|---|---|---|
| Time to polished reactive UI | Fastest — widgets re-run the script; minimal boilerplate | Medium — callbacks, layouts, and deployment wiring | Slowest for this scope — desktop lifecycle, packaging |
| Interactive charts | Plotly first-class via `st.plotly_chart` | Native Plotly / Dash Graph | Matplotlib or embed Plotly/WebEngine; more glue |
| Quant-desk internal tool | De facto standard for analyst utilities; browser shareable | Strong for multi-page product UIs | Best when offline desktop install is required |
| Slider-driven workflow | Ideal — drag updates state and redraws immediately | Excellent with `dcc.Slider` + callbacks; more code | Excellent latency; heavier to ship |

**Decision:** Streamlit + Plotly. The product is a single-session, slider-driven teaching
utility. Streamlit maps that interaction model directly (control change → recompute →
redraw) with the least ceremony, while Plotly supplies publication-quality interactive
charts. Dash would only win if we needed a multi-route product shell or finer callback
graphs; PySide6 would win for a packaged offline desktop binary — neither is the goal
here.

## Module layout

```
bayes_app/
  math_core.py   # Pure Bayes functions (no UI imports)
  models.py      # Pydantic state / validation
  modes.py       # Scenario text, labels, defaults
  viz.py         # Plotly figure builders
  app.py         # Streamlit UI composition
tests/
  test_math_core.py
```

Data flows one way: **mode defaults → validated inputs → math → viz → Streamlit render**.
The math layer never imports Streamlit or Plotly, so it stays unit-testable in isolation.

## Run path

`uv run streamlit run bayes_app/app.py` (also exposed via `uv run bayes-app` → `main.py`).
