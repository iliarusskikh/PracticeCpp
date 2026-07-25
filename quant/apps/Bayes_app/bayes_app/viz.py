"""Plotly visualization builders for Bayes teaching views."""

from __future__ import annotations

import math

import plotly.graph_objects as go

from bayes_app.math_core import (
    ContingencyCounts,
    natural_frequencies,
    sensitivity_curve,
)

# Desk-utility palette: cool slate + amber accent (avoid purple/cream AI defaults).
_COLOR = {
    "tp": "#0F766E",  # teal — true positives
    "fp": "#C2410C",  # burnt orange — false positives
    "fn": "#0369A1",  # steel blue — false negatives
    "tn": "#64748B",  # slate — true negatives
    "prior": "#94A3B8",
    "posterior": "#D97706",  # amber highlight
    "curve": "#0EA5E9",
    "grid": "#1E293B",
    "paper": "#0B1220",
    "font": "#E2E8F0",
    "muted": "#94A3B8",
}

_LAYOUT_BASE: dict[str, object] = {
    "paper_bgcolor": _COLOR["paper"],
    "plot_bgcolor": "#111827",
    "font": {"color": _COLOR["font"], "family": "IBM Plex Sans, Segoe UI, sans-serif"},
    "margin": {"l": 56, "r": 24, "t": 48, "b": 48},
    "hoverlabel": {"bgcolor": "#1E293B", "font_size": 12},
}


def _layout(**overrides: object) -> dict[str, object]:
    """Merge figure layout overrides onto the shared base (later keys win)."""
    return {**_LAYOUT_BASE, **overrides}


def _pct(count: float, n: int) -> float:
    return 100.0 * count / n if n else 0.0


def frequency_grid_figure(
    prior: float,
    likelihood: float,
    false_positive: float,
    *,
    n: int = 1000,
    hypothesis_label: str = "H",
    evidence_label: str = "E",
) -> go.Figure:
    """Build a natural-frequency icon grid (≈N cells) colored by TP/FP/FN/TN.

    Args:
        prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).
        n: Population size (ideally a perfect square for a clean grid).
        hypothesis_label: Short label for H used in the legend.
        evidence_label: Short label for E used in the legend.

    Returns:
        A Plotly figure with a scatter grid of category markers.
    """
    counts = natural_frequencies(prior, likelihood, false_positive, n=n)
    # Allocate integer cell counts that sum exactly to n (largest-remainder method).
    raw = [counts.tp, counts.fp, counts.fn, counts.tn]
    floors = [math.floor(v) for v in raw]
    remainder = n - sum(floors)
    order = sorted(range(4), key=lambda i: raw[i] - floors[i], reverse=True)
    ints = floors[:]
    for i in range(remainder):
        ints[order[i % 4]] += 1
    n_tp, n_fp, n_fn, n_tn = ints

    side = int(math.ceil(math.sqrt(n)))
    categories = (
        [("TP", _COLOR["tp"])] * n_tp
        + [("FP", _COLOR["fp"])] * n_fp
        + [("FN", _COLOR["fn"])] * n_fn
        + [("TN", _COLOR["tn"])] * n_tn
    )

    xs: list[int] = []
    ys: list[int] = []
    colors: list[str] = []
    texts: list[str] = []
    for idx, (cat, color) in enumerate(categories):
        xs.append(idx % side)
        ys.append(side - 1 - idx // side)
        colors.append(color)
        texts.append(cat)

    fig = go.Figure(
        data=go.Scatter(
            x=xs,
            y=ys,
            mode="markers",
            marker={
                "size": max(4, min(10, 420 // side)),
                "color": colors,
                "symbol": "square",
                "line": {"width": 0},
            },
            text=texts,
            hovertemplate="%{text}<extra></extra>",
            showlegend=False,
        )
    )

    # Manual legend via invisible traces for stable ordering.
    legend_items = [
        (f"TP — {hypothesis_label} ∧ {evidence_label} ({n_tp})", _COLOR["tp"]),
        (f"FP — ¬{hypothesis_label} ∧ {evidence_label} ({n_fp})", _COLOR["fp"]),
        (f"FN — {hypothesis_label} ∧ ¬{evidence_label} ({n_fn})", _COLOR["fn"]),
        (f"TN — ¬{hypothesis_label} ∧ ¬{evidence_label} ({n_tn})", _COLOR["tn"]),
    ]
    for name, color in legend_items:
        fig.add_trace(
            go.Scatter(
                x=[None],
                y=[None],
                mode="markers",
                marker={"size": 10, "color": color, "symbol": "square"},
                name=name,
            )
        )

    fig.update_layout(
        **_layout(
            title={
                "text": f"Natural frequencies (N = {n:,})",
                "x": 0.01,
                "xanchor": "left",
            },
            xaxis={"visible": False, "range": [-1, side]},
            yaxis={
                "visible": False,
                "range": [-1, side],
                "scaleanchor": "x",
                "scaleratio": 1,
            },
            legend={
                "orientation": "h",
                "yanchor": "bottom",
                "y": -0.18,
                "x": 0,
                "font": {"size": 11},
            },
            height=460,
            margin={"l": 16, "r": 16, "t": 48, "b": 72},
        )
    )
    return fig


def sensitivity_figure(
    prior: float,
    likelihood: float,
    false_positive: float,
    *,
    posterior: float | None,
) -> go.Figure:
    """Plot posterior vs prior with the current operating point marked.

    Args:
        prior: Current P(H).
        likelihood: Fixed P(E|H).
        false_positive: Fixed P(E|¬H).
        posterior: Current P(H|E), or ``None`` if undefined.

    Returns:
        A Plotly line chart with a marker at the active prior.
    """
    curve = sensitivity_curve(likelihood, false_positive, n_points=201)
    xs = [p for p, _ in curve]
    ys = [post if post is not None else float("nan") for _, post in curve]

    fig = go.Figure()
    fig.add_trace(
        go.Scatter(
            x=xs,
            y=ys,
            mode="lines",
            name="P(H|E) vs prior",
            line={"color": _COLOR["curve"], "width": 2.5},
            hovertemplate="Prior %{x:.3f}<br>Posterior %{y:.3f}<extra></extra>",
        )
    )
    # Identity reference: posterior = prior (uninformative evidence).
    fig.add_trace(
        go.Scatter(
            x=[0, 1],
            y=[0, 1],
            mode="lines",
            name="P(H|E) = P(H)",
            line={"color": _COLOR["muted"], "width": 1, "dash": "dot"},
            hoverinfo="skip",
        )
    )
    if posterior is not None:
        fig.add_trace(
            go.Scatter(
                x=[prior],
                y=[posterior],
                mode="markers",
                name="Current",
                marker={
                    "size": 12,
                    "color": _COLOR["posterior"],
                    "line": {"width": 1.5, "color": "#FFF7ED"},
                },
                hovertemplate=(
                    f"Prior {prior:.4f}<br>Posterior {posterior:.4f}<extra>Current</extra>"
                ),
            )
        )

    fig.update_layout(
        **_layout(
            title={
                "text": "Sensitivity of posterior to prior",
                "x": 0.01,
                "xanchor": "left",
            },
            xaxis={
                "title": "Prior P(H)",
                "range": [0, 1],
                "gridcolor": "#1F2937",
                "zeroline": False,
            },
            yaxis={
                "title": "Posterior P(H|E)",
                "range": [0, 1],
                "gridcolor": "#1F2937",
                "zeroline": False,
            },
            legend={"orientation": "h", "y": 1.08, "x": 0},
            height=380,
        )
    )
    return fig


def contingency_figure(
    counts: ContingencyCounts,
    *,
    hypothesis_label: str = "H",
    evidence_label: str = "E",
) -> go.Figure:
    """Render a 2×2 contingency / confusion matrix with counts and percentages.

    Args:
        counts: Natural-frequency cell counts.
        hypothesis_label: Row-label fragment for H.
        evidence_label: Column-label fragment for E.

    Returns:
        A Plotly annotated heatmap-style table figure.
    """
    n = counts.n
    z = [[counts.tp, counts.fn], [counts.fp, counts.tn]]
    text = [
        [
            f"TP<br>{counts.tp:.1f}<br>({_pct(counts.tp, n):.1f}%)",
            f"FN<br>{counts.fn:.1f}<br>({_pct(counts.fn, n):.1f}%)",
        ],
        [
            f"FP<br>{counts.fp:.1f}<br>({_pct(counts.fp, n):.1f}%)",
            f"TN<br>{counts.tn:.1f}<br>({_pct(counts.tn, n):.1f}%)",
        ],
    ]
    colorscale = [
        [0.0, "#0F172A"],
        [0.35, "#134E4A"],
        [0.7, "#0F766E"],
        [1.0, "#14B8A6"],
    ]
    fig = go.Figure(
        data=go.Heatmap(
            z=z,
            x=[f"{evidence_label}", f"¬{evidence_label}"],
            y=[f"{hypothesis_label}", f"¬{hypothesis_label}"],
            text=text,
            texttemplate="%{text}",
            textfont={"size": 13, "color": _COLOR["font"]},
            colorscale=colorscale,
            showscale=False,
            hovertemplate="%{y} ∧ %{x}<br>count %{z:.2f}<extra></extra>",
        )
    )
    fig.update_layout(
        **_layout(
            title={"text": f"Contingency table (N = {n:,})", "x": 0.01, "xanchor": "left"},
            xaxis={"side": "top", "title": "Evidence"},
            yaxis={"autorange": "reversed", "title": "Hypothesis"},
            height=360,
        )
    )
    return fig


def belief_comparison_figure(prior: float, posterior: float | None) -> go.Figure:
    """Bar chart comparing prior belief to posterior belief.

    Args:
        prior: P(H).
        posterior: P(H|E), or ``None`` if undefined.

    Returns:
        A Plotly bar figure.
    """
    post_val = posterior if posterior is not None else 0.0
    fig = go.Figure(
        data=[
            go.Bar(
                x=["Prior P(H)", "Posterior P(H|E)"],
                y=[prior, post_val],
                marker_color=[_COLOR["prior"], _COLOR["posterior"]],
                text=[
                    f"{prior:.4f}",
                    "undefined" if posterior is None else f"{posterior:.4f}",
                ],
                textposition="outside",
                hovertemplate="%{x}: %{y:.4f}<extra></extra>",
            )
        ]
    )
    fig.update_layout(
        **_layout(
            title={"text": "Prior vs posterior belief", "x": 0.01, "xanchor": "left"},
            yaxis={"title": "Probability", "range": [0, 1.15], "gridcolor": "#1F2937"},
            xaxis={"title": None},
            height=320,
            showlegend=False,
            margin={"l": 56, "r": 24, "t": 48, "b": 40},
        )
    )
    if posterior is None:
        fig.add_annotation(
            text="P(E)=0 → posterior undefined",
            xref="paper",
            yref="paper",
            x=0.75,
            y=0.9,
            showarrow=False,
            font={"color": "#F87171", "size": 12},
        )
    return fig


def formula_values_row(
    result_prior: float,
    likelihood: float,
    false_positive: float,
    evidence: float,
    posterior: float | None,
) -> go.Figure:
    """Compact numeric strip shown under the LaTeX formula.

    Args:
        result_prior: P(H).
        likelihood: P(E|H).
        false_positive: P(E|¬H).
        evidence: P(E).
        posterior: P(H|E), or ``None`` if undefined.

    Returns:
        A Plotly annotation strip figure.
    """
    labels = ["P(H)", "P(E|H)", "P(E|¬H)", "P(E)", "P(H|E)"]
    vals = [
        f"{result_prior:.4f}",
        f"{likelihood:.4f}",
        f"{false_positive:.4f}",
        f"{evidence:.4f}",
        "—" if posterior is None else f"{posterior:.4f}",
    ]
    colors = [
        _COLOR["prior"],
        _COLOR["curve"],
        _COLOR["fp"],
        _COLOR["muted"],
        _COLOR["posterior"],
    ]
    fig = go.Figure()
    for i, (lab, val, col) in enumerate(zip(labels, vals, colors, strict=True)):
        x = (i + 0.5) / 5
        fig.add_annotation(
            x=x,
            y=0.62,
            text=f"<b>{val}</b>",
            showarrow=False,
            font={"size": 22, "color": col},
            xref="paper",
            yref="paper",
        )
        fig.add_annotation(
            x=x,
            y=0.22,
            text=lab,
            showarrow=False,
            font={"size": 12, "color": _COLOR["muted"]},
            xref="paper",
            yref="paper",
        )
    fig.update_layout(
        **_layout(
            height=90,
            xaxis={"visible": False, "range": [0, 1]},
            yaxis={"visible": False, "range": [0, 1]},
            margin={"l": 8, "r": 8, "t": 8, "b": 8},
        )
    )
    return fig
